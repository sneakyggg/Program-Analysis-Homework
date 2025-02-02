#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/GraphWriter.h"
#include "analysis.h"

using namespace llvm;

static inline void printFunctions (llvm::Module& module)
{
    outs() <<"@@printFunctions \n";

    for (const auto &function : module) 
    {
        outs() << "Function: " << function.getName() << "\n";

        const FunctionType *funcType = function.getFunctionType();
        outs() << "\t>>Type: " << *funcType << "\n";

        if (function.isDeclaration()) 
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

static inline void printBasicBlockStats(const Module& module) 
{
    outs() << "@@printBasicBlockStats\n";

    for (const auto &function : module) 
    {
        unsigned int basicBlockCount = 0;
        for (const auto &bb : function) 
        {
            basicBlockCount++;
        }

        outs() << "Function: " << function.getName() << "\n";
        outs() << "\tNumber of Basic Blocks: " << basicBlockCount << "\n";
    }
}


static inline void printInstructions (const Module& module)
{
    errs() << "@@printInstructions\n";

    for (const auto &function : module) 
    {
        if (function.isDeclaration())
            continue;

        outs() << "Function: " << function.getName() << "\n";
        for (const auto &bb : function) 
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

static inline void printCallGraph(const Module& module) 
{
    errs() << "@@printCallGraph\n";

    std::map<std::string, std::set<std::string>> callGraph;
    for (const auto &function : module) 
    {
        std::string callerName = function.getName().str();
        callGraph[callerName] = std::set<std::string>();

        for (const auto &bb : function) 
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


void DumpCallGraph(CallGraph &CG, const std::string &FileName)
{
    std::error_code EC;
    raw_fd_ostream File(FileName, EC, sys::fs::OF_Text);

    if (!EC) 
    {
        File << "digraph CallGraph {\n";
        std::set<std::pair<std::string, std::string>> uniqueEdges;
                
        for (auto &node : CG) 
        {
            const Function *F = node.first;
            if (!F || F->isDeclaration()) continue;

            std::string FuncName = F->getName().str();
            File << "\"" << FuncName << "\";\n";

            CallGraphNode *CGN = node.second.get();
            for (unsigned i = 0; i < CGN->size(); ++i) 
            {
                CallGraphNode *CalleeNode = CGN->operator[](i);
                Function *Callee = CalleeNode->getFunction();
                if (Callee && !Callee->isDeclaration()) 
                {
                    std::string CalleeName = Callee->getName().str();
                    if (uniqueEdges.insert({FuncName, CalleeName}).second) 
                    {
                        File << "\"" << FuncName << "\" -> \"" << CalleeName << "\";\n";
                    }
                }
            }
        }

        File << "}\n";
        errs() << "Call graph saved to " << FileName << "\n";
    } 
    else 
    {
        errs() << "Error opening file: " << EC.message() << "\n";
    }
}

bool genCallGraph (Module &M) 
{
    CallGraph CG(M);

    DumpCallGraph (CG, "callgraph.dot");
    return false;
}


void analyzeModule(llvm::Module& module, string type) 
{
    if (type == "function")
        printFunctions (module);

    if (type == "block")
        printBasicBlockStats (module);

    if (type == "inst")
        printInstructions (module);

    if (type == "cg")
    {
        printCallGraph (module);
        genCallGraph (module);
    }
}
