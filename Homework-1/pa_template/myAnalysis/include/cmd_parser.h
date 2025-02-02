#ifndef __CMD_PARSER_H__
#define __CMD_PARSER_H__
#include <iostream>
#include <unistd.h>
#include <string>
#include <unordered_map>

#include <iostream>
#include <unistd.h>  // For getopt
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include <iostream>
#include <unistd.h>  // For getopt
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

struct Option 
{
    char shortFlag;
    string value;
    string description;

    Option(char flag, string val, string desc)
        : shortFlag(flag), value(val), description(desc) {}
};

class CommandLineParser 
{
public:
    CommandLineParser(int argc, char* argv[]) : argc(argc), argv(argv)
    {
        optTable = 
        {
            {'h', Option('h', "bool", "Show this help message")},
        };
    }

    void parse() 
    {
        string optString = genOptString();

        int opt;
        while ((opt = getopt(argc, argv, optString.c_str())) != -1) 
        {
            auto it = optTable.find(opt);
            if (it != optTable.end()) 
            {
                if (optarg != NULL)
                {
                    dynOpts.insert ({opt, Option(opt, string(optarg), it->second.description)}); 
                }
                else
                {
                    dynOpts.insert ({opt, Option(opt, it->second.value, it->second.description)});
                }        
            } 
            else 
            {
                printf ("@@CommandLineParser: parse option [-%c] failed \n", opt);
                help();
                exit(0);
            }
        }

        if (dynOpts.size () == 0)
        {
            help();
        }

        return;
    }

    void addOption(char shortFlag, string value, string description)
    {
        optTable.insert ({shortFlag, Option(shortFlag, value, description)});
        return;
    }

    string getOption(const string& opt) const 
    {
        const Option* optItem = getOptItem(opt);
        if (optItem == NULL)
        {
            return "";
        }
        return optItem->value;
    }

    bool hasOption(const string& opt) const 
    {
        const Option* optItem = getOptItem(opt);
        return (optItem != NULL);
    }

    void help() const 
    {
        cout<<"\n";
        cout<< "##############################################################################\n";
        cout<< "Usage: " << argv[0] << " [options]\n";
        cout<< "##############################################################################\n";
        cout<< "Options:\n";
        for (const auto& entry : optTable) 
        {
            if (entry.second.value == "bool")
            {
                cout << "  -" << entry.first << "         " << entry.second.description << "\n";
            }
            else
            {
                cout << "  -" << entry.first << " <arg>   " << entry.second.description << "\n";
            }         
        }
        cout<< "##############################################################################\n\n";
    }

private:
    int argc;
    char** argv;
    unordered_map<char, Option> optTable;
    unordered_map<char, Option> dynOpts;

private:
    inline string genOptString() 
    {
        ostringstream ss;
        for (const auto& entry : optTable) 
        {
            if (entry.second.value == "bool")
            {
                ss << entry.first;
            } 
            else 
            {
                ss << entry.first << ":";
            }
        }
        
        return ss.str();
    }

    inline const Option* getOptItem(const string& opt) const
    {
        if (opt.length() == 1)
        {
            char shortFlag = opt[0];
            auto it = dynOpts.find(shortFlag);
            if (it != dynOpts.end()) 
            {
                return &(it->second);
            }
        }
        return NULL;
    }
};

#endif