#!/bin/bash

installGraphviz()
{
    if ! command -v dot &> /dev/null
    then
        echo "Graphviz (dot) is not installed. Attempting to install..."
        if command -v apt-get &> /dev/null; then
            sudo apt-get update && sudo apt-get install -y graphviz
        else
            echo "Unsupported package manager. Please install Graphviz manually."
            exit 1
        fi

        if ! command -v dot &> /dev/null; then
            echo "Error: Failed to install Graphviz. Please install it manually."
            exit 1
        fi
        echo "Graphviz installed successfully."
    fi
}

convertPng () 
{
    local dotFile=$1
    if [ ! -f "$dotFile" ]; then
        echo "Error: Input file '$dotFile' does not exist."
        exit 1
    fi

    local pngFIle="$dotFile.png"
    if dot -Tpng "$dotFile" -o "$pngFIle"; then
        echo "Conversion successful: '$dotFile' -> '$pngFIle'"
    else
        echo "Error: Conversion failed."
        exit 1
    fi
}


main() 
{
    installGraphviz

    local dotFile=$1
    convertPng "$dotFile"
}


main "$@"