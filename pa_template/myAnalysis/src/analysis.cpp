#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/GraphWriter.h"
#include "analysis.h"
#include "pag.h"
#include "cfg.h"
#include "icfg.h"
#include "otf_pta.h"
#include "dfg.h"

using namespace llvm;
map<llvm::Value*, set<llvm::CallBase*>> CG::value2IndirectCS;

static inline void printFunctions (LLVM& llvmParser)
{
    outs() <<"@@printFunctions \n";

    for (auto it = llvmParser.func_begin (); it != llvmParser.func_end (); it++) 
    {
        Function *function = *it;
        outs() << "Function: " << function->getName() << "\n";

        const FunctionType *funcType = function->getFunctionType();
        outs() << "\t>>Type: " << *funcType << "\n";

        if (function->isDeclaration()) 
        {
            outs() << "\t>>Function is a declaration\n";
        } 
        else 
        {
            outs() << "\t>>Function is a definition\n";
        }

        outs() <<"\n";
    }
}

static inline void printBasicBlockStats(LLVM& llvmParser) 
{
    outs() << "@@printBasicBlockStats\n";

    for (auto it = llvmParser.func_begin (); it != llvmParser.func_end (); it++) 
    {
        Function *function = *it;

        unsigned int basicBlockCount = 0;
        for (const auto &bb : *function) 
        {
            basicBlockCount++;
        }

        outs() << "Function: " << function->getName() << "\n";
        outs() << "\tNumber of Basic Blocks: " << basicBlockCount << "\n";
    }
}


static inline void printInstructions (LLVM& llvmParser)
{
    errs() << "@@printInstructions\n";

    for (auto it = llvmParser.func_begin (); it != llvmParser.func_end (); it++) 
    {
        llvm::Function *function = *it;

        if (function->isDeclaration())
            continue;

        outs() << "Function: " << function->getName() << "\n";
        for (const auto &bb : *function) 
        {
            for (const auto &instr : bb) 
            {
                StringRef opcodeName = instr.getOpcodeName();
                outs() << "    [" << opcodeName << "] " << instr << "\n";
            }
        }

        outs() << "\n";
    }
}

static inline void printCG (std::map<std::string, std::set<std::string>>& callGraph)
{
    for (const auto &caller : callGraph) 
    {
        outs() << "Function: " << caller.first << "\n";
        if (!caller.second.empty())
        {
            outs() << "  Calls:\n";
            for (const auto &callee : caller.second) 
            {
                outs() << "    - " << callee << "\n";
            }
        }
        else
        {
            outs() << "  Calls: None\n";
        }

        outs() << "\n";
    }
}

static inline void printCallGraph(LLVM& llvmParser) 
{
    errs() << "@@printCallGraph\n";

    std::map<std::string, std::set<std::string>> callGraph;
    for (auto it = llvmParser.func_begin (); it != llvmParser.func_end (); it++) 
    {
        Function *function = *it;

        std::string callerName = function->getName().str();
        callGraph[callerName] = std::set<std::string>();

        for (const auto &bb : *function) 
        {
            for (const auto &instr : bb) 
            {
                if (const CallBase *call = dyn_cast<CallBase>(&instr)) 
                {
                    if (Function *calledFunc = call->getCalledFunction()) 
                    {
                        std::string calleeName = calledFunc->getName().str();
                        callGraph[callerName].insert(calleeName);
                    }
                }
            }
        }
    }

    printCG (callGraph);    
}


void buildCG (LLVM& llvmParser, const std::string &Filename = "cg") 
{
    CG cg (&llvmParser);
    cg.build ();

    CGVisual vis (Filename, &cg);
    vis.witeGraph();

    return;
}

void buildCFG (LLVM& llvmParser, const std::string &Filename = "cfg") 
{
    for (auto it = llvmParser.func_begin(); it != llvmParser.func_end(); ++it) 
    {
        llvm::Function* F = *it;
        if (F->isDeclaration()) continue;

        CFG cfg;
        cfg.build(*F);
            
        CFGVisual vis (F->getName().str() + "_" + Filename, &cfg);
        vis.witeGraph();
    } 
}

void buildICFG (LLVM& llvmParser, const std::string &Filename = "icfg") 
{
    ICFG icfg (&llvmParser);
    icfg.build ();

    ICFGVisual vis (Filename, &icfg);
    vis.witeGraph();
}

void buildPAG (LLVM& llvmParser, const std::string &Filename = "pag") 
{
    ICFG icfg (&llvmParser);
    icfg.build ();

    PAG pag (&icfg);
    pag.build();
    
    PAGVis vis(Filename, &pag);
    vis.witeGraph();

    return;
}

void runPTA (LLVM& llvmParser)
{
    ICFG icfg (&llvmParser);
    icfg.build ();

    OTFPTA pta (icfg);
    pta.solve ();
}

void runDFA (LLVM& llvmParser)
{
    ICFG icfg (&llvmParser);
    icfg.build ();

    OTFPTA pta (icfg, false);
    pta.solve ();

    DFG dfg (icfg, pta);
    dfg.build ();
    
    DFGVisual vis("dfg", &dfg);
    vis.witeGraph();
}


void analyzeModule(LLVM& llvmParser, string type) 
{
    if (type == "function")
        printFunctions (llvmParser);

    if (type == "block")
        printBasicBlockStats (llvmParser);

    if (type == "inst")
        printInstructions (llvmParser);

    if (type == "cg")
    {
        buildCG (llvmParser);
    }

    if (type == "cfg")
    {
        buildCFG (llvmParser);
    }

    if (type == "icfg")
    {
        buildICFG (llvmParser);
    }

    if (type == "pag")
    {
        buildPAG (llvmParser);
    }

    if (type == "pta")
    {
        runPTA (llvmParser);
    }

    if (type == "dfa")
    {
        runDFA (llvmParser);
    }
}
