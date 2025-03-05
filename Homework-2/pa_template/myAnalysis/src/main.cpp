#include "cmd_parser.h"
#include "analysis.h"

// external function
void testEntry ();

static inline void addCmdOptions (CommandLineParser& cmdParser)
{
    // Add your new option here
    cmdParser.addOption('b', "", "Specify the path of LLVM bitcode file for analysis");
    cmdParser.addOption('f', "", "Specify the functionality: function, block, inst, cg, cfg, pag");
    cmdParser.addOption('t', "bool", "Perform the test for the code");
}

int main(int argc, char** argv) 
{
    CommandLineParser cmdParser(argc, argv);
    addCmdOptions (cmdParser);
    cmdParser.parse ();
    
    if (cmdParser.hasOption("h")) 
    {
        cmdParser.help ();
        return 0;
    }

    if (cmdParser.hasOption("t")) 
    {
        testEntry ();
        return 0;
    }

    if (cmdParser.hasOption("b"))
    {
        string bcFile = cmdParser.getOption ("b");
        LLVM llvmParser (bcFile);

        analyzeModule (llvmParser, cmdParser.getOption ("f"));
    }

    return 0;
}
