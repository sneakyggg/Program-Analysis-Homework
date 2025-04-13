#ifndef _ICFG_H_
#define _ICFG_H_
#include "cfg.h"
#include "cg.h"

class ICFG : public GenericGraph<CFGNode, CFGEdge> 
{
public:
    typedef map<llvm::Function*, CFG*>::iterator cfg_iteratoir;

    ICFG(LLVM *llvmpas = NULL) { llvmParser = llvmpas; }
    ~ICFG() 
    {
        delete cg;
        for (auto itr = cfg_begin (); itr != cfg_end (); itr++)
        {
            delete itr->second;
        }
    }
    
    void build() 
    {
        buildCFGs();

        cg = new CG (llvmParser);
        assert(cg != NULL);
        cg->build();

        buildICFG(cg);
        return;
    }

    void refine(llvm::Value *fpVal,
                const std::unordered_set<llvm::Function*> &callees)
    {
        set<llvm::CallBase*> callSites = CG::getCallsites (fpVal);
        if (callSites.empty()) 
        {
            return;
        }

        cg->refine (callSites, callees);

        for (llvm::CallBase *callInst : callSites)
        {
            llvm::Function* caller = callInst->getParent ()->getParent();
            CFG* callerCFG = getCFG(caller);
            CFGNode* csNode = callerCFG->getCFGNode (callInst);
            assert (csNode != NULL);

            for (auto *callee : callees)
            {
                CFG* calleeCFG = getCFG(callee);
                if (calleeCFG == NULL)
                {
                    continue;
                }

                CFGNode* calleeEntry = calleeCFG->getEntryNode();
                CFGNode* calleeExit = calleeCFG->getExitNode();

                addEdge(new CFGEdge(csNode, calleeEntry));
                addEdge(new CFGEdge(calleeExit, csNode));
            }
        }
    }

    cfg_iteratoir cfg_begin () { return func2CFG.begin (); }
    cfg_iteratoir cfg_end () { return func2CFG.end (); }
    LLVM* getLLVMParser () { return llvmParser; }
    CG* getCG () { return cg; }
    inline CFG* getCFG (llvm::Function* F)
    {
        auto it = func2CFG.find (F);
        if (it == func2CFG.end ())
        {
            return NULL;
        }
        return it->second;
    }
    
private:
    void buildCFGs()
    {
        if (!llvmParser) return;

        unsigned nodeId = 1;
        for (auto it = llvmParser->func_begin(); it != llvmParser->func_end(); ++it) 
        {
            llvm::Function* F = *it;
            if (F->isDeclaration()) continue;

            CFG *cfg = new CFG(nodeId);
            assert (cfg != NULL);
            cfg->build(*F);
            
            func2CFG [F] = cfg;
            nodeId += cfg->getNodeNum ();
        }

        return;
    }

    void buildICFG(CG *cg) 
    {
        for (auto itNode = cg->begin (); itNode != cg->end (); itNode++) 
        {
            CGNode* callerCGNode = itNode->second;
            llvm::Function* callerFunc = callerCGNode->getLLVMFunc();

            CFG* callerCFG = getCFG(callerFunc);
            if (!callerCFG) continue;
            
            for (auto itEdge = callerCGNode->outEdgeBegin(); itEdge != callerCGNode->outEdgeEnd (); itEdge++)
            {
                CGEdge* edge = *itEdge;
                CGNode* calleeCGNode = edge->getDstNode ();
                llvm::Function* calleeFunc = calleeCGNode->getLLVMFunc();

                CFG* calleeCFG = getCFG(calleeFunc);
                if (calleeCFG == NULL)
                {
                    continue;
                }
                
                vector<CFGNode*> callSiteCFGNodes = getCallsiteNodes(callerCFG, callerCGNode, calleeFunc);
                CFGNode* calleeEntry = calleeCFG->getEntryNode();
                CFGNode* calleeExit = calleeCFG->getExitNode();
                    
                for (CFGNode* callSite : callSiteCFGNodes)
                {
                    addEdge(new CFGEdge(callSite, calleeEntry));
                    addEdge(new CFGEdge(calleeExit, callSite));
                }   
            }
        }
    }

private:
    LLVM *llvmParser;
    CG *cg;
    map<llvm::Function*, CFG*> func2CFG;

private:
    inline vector<CFGNode*> getCallsiteNodes(CFG* callerCFG, CGNode* cgNode, llvm::Function* calleeFunc) 
    {
        vector<CFGNode*> csNodes;
        for (auto itCs = cgNode->begin (); itCs != cgNode->end (); itCs++) 
        {
            llvm::CallBase* callInst = *itCs;
            llvm::Function* callee = callInst->getCalledFunction();
            if (callee != calleeFunc)
            {
                continue;
            }

            CFGNode* cfgNode = callerCFG->getCFGNode (callInst);
            assert (cfgNode != NULL);
            csNodes.push_back (cfgNode);
        }

        return csNodes;
    }
};

class ICFGVisual : public GraphVis<CFGNode, CFGEdge, ICFG>
{
public:
    ICFGVisual(std::string graphName, ICFG* graph)
        : GraphVis<CFGNode, CFGEdge, ICFG>(graphName, graph) {}
    
    ~ICFGVisual() {}

    inline string getNodeLabel (CFGNode *node)
    {
        if (node->isEntry ())
        {
            CFGEntryNode* enNode = (CFGEntryNode*)node;
            llvm::Function* func = enNode->getFunction ();
            return LLVM().getValueLabel (func);
        }
        else if (node->isExit ())
        {
            return "exit";
        }
        else
        {
            llvm::Instruction* inst = node->getInstruction ();
            std::string instStr = LLVM().getValueLabel (inst);;
            return escapeForDotLabel (instStr);
        }
    }

    inline void writeCFGNodes (CFG *cfg)
    {
        for (auto it = cfg->begin (), end = cfg->end (); it != end; it++)
        {
            CFGNode *node = it->second;
            if (!IsVizNode (node))
            {
                continue;
            }
            writeNodes (node);
        }
    }

    inline void writeCFGAllEdges (CFG *cfg)
    {
        for (auto it = cfg->begin (), end = cfg->end (); it != end; it++)
        {
            CFGNode *node = it->second;
            if (!IsVizNode (node))
            {
                continue;
            }

            for (auto itEdge = node->outEdgeBegin (), itEnd = node->outEdgeEnd (); itEdge != itEnd; itEdge++)
            {
                CFGEdge *edge = *itEdge;
                if (!IsVizNode (edge->getDstNode()))
                {
                    continue;
                }
                
                writeEdge (edge);
            }
        }
    }

    void witeGraph () 
    {
        writeHeader(m_GraphName);

        // write nodes
        fprintf(m_File, "\t// Define the nodes\n");
        for (auto it = m_Graph->cfg_begin (), end = m_Graph->cfg_end (); it != end; it++)
        {
            CFG *cfg = it->second;
            writeCFGNodes (cfg);
        }
        //writeAllNodes (m_Graph);
        fprintf(m_File, "\n\n");

        // write edges
        fprintf(m_File, "\t// Define the edges\n");
        for (auto it = m_Graph->cfg_begin (), end = m_Graph->cfg_end (); it != end; it++)
        {
            CFG *cfg = it->second;
            writeCFGAllEdges (cfg);
        }
        //writeAllEdges (m_Graph);
        fprintf(m_File, "}\n");
    }

    inline string getNodeAttributes(CFGNode *node) 
    {
        string str = "shape=rectangle, color=black";   
        return str;
    }  
};

#endif