#ifndef _DFG_H_
#define _DFG_H_
#include "icfg.h"
#include "otf_pta.h"

using namespace std;

using DFGNode = CFGNode;
using DFGEdge = CFGEdge;
class DFG : public GenericGraph<DFGNode, DFGEdge>
{
public:
    typedef set<llvm::Value*> ValueSet;
    typedef map<DFGNode*, ValueSet> DFASet;

    DFG(ICFG& icfg, OTFPTA& pta) : icfg(&icfg), pta(&pta)
    {
        llvmParser = icfg.getLLVMParser ();
    }
    ~DFG() = default;

    void build() 
    {
        // 1. intra-procedural DFA
        for (auto itr = icfg->cfg_begin (); itr != icfg->cfg_end (); itr++)
        {
            CFG* cfg = itr->second;
            performDFA (cfg);
        }

        // 2. inter-procedural DFA
        buildIDFG();

        // 3. handle globals
        // skip here
    }

    ICFG* getICFG() { return icfg; }
private:
    LLVM* llvmParser;
    ICFG *icfg;
    OTFPTA *pta;
    map<llvm::Value*, set<DFGNode*>> defToNode;

private:
    inline DFASet initializeGEN (CFG *cfg)
    {
        DFASet GEN;
        for (auto itNode = cfg->begin (); itNode != cfg->end (); itNode++) 
        {
            DFGNode* node = itNode->second;
            GEN[node] = getDefinitions (node);
        }

        return GEN;
    }

    inline DFASet initializeKILL (CFG *cfg, DFASet& GEN)
    {
        DFASet KILL;
        for (auto itNode = cfg->begin (); itNode != cfg->end (); itNode++) 
        {
            DFGNode* node = itNode->second;

            ValueSet& nodeGEN = GEN[node];
            if (nodeGEN.size () == 0)
            {
                continue;
            }

            for (auto itOther = cfg->begin (); itOther != cfg->end (); itOther++) 
            {
                DFGNode* otherNode = itOther->second;
                if (otherNode == node)
                {
                    continue;
                }

                ValueSet& otherGEN = GEN[otherNode];
                for (auto v : otherGEN)
                {
                    // here we assume ALLOC is binded with the memory obj
                    if (nodeGEN.count (v) && !llvm::isa<llvm::AllocaInst>(v))
                    {
                        KILL[node].insert (v);
                    }
                }
            }
        }

        return KILL;
    }

    inline DFASet initializeSET (CFG *cfg)
    {
        DFASet dfaSet;
        for (auto itNode = cfg->begin (); itNode != cfg->end (); itNode++) 
        {
            DFGNode* node = itNode->second;
            dfaSet[node] = ValueSet();
        }

        return dfaSet;
    }

    // implicit def
    inline void handleStore(llvm::Instruction* inst, ValueSet& defs) 
    {
        llvm::StoreInst *SI = llvm::dyn_cast<llvm::StoreInst>(inst);
        PTS pts = pta->getPTS (SI->getPointerOperand());
        for (auto it = pts.begin (); it != pts.end (); it++)
        {
            PAGNode* pagNode = *it;
            defs.insert (pagNode->value);
        }

        return;
    }

    inline ValueSet getDefinitions(DFGNode* node) 
    {
        ValueSet defs, uses;
        llvm::Instruction* inst = node->getInstruction ();

        // Special handling: Entry node defines function arguments
        if (node->isEntry())
        {
            llvm::Function* function = ((CFGEntryNode*)node)->getFunction();
            for (llvm::Argument &arg : function->args())
            {
                defs.insert(&arg);

                auto& nodeSet = defToNode[&arg];
                nodeSet.insert (node);
            }
            return defs;
        }
        else if (node->isExit() || inst == nullptr)
        {
            return defs;
        }
        else if (llvmParser->isStore (inst))
        { 
            //imoplicit defition
            handleStore (inst, defs);
        }
        else
        {
            // explicit definition
            llvmParser->getDefUse (inst, defs, uses);
        }

        // update def to node mapping
        for (auto def : defs)
        {
            auto& nodeSet = defToNode[def];
            nodeSet.insert (node);
        }

        return defs;
    }

    // implicit use
    inline void handleLoad(llvm::Instruction* inst, ValueSet& uses) 
    {
        auto *loadInst = llvm::dyn_cast<llvm::LoadInst>(inst);
        PTS pts = pta->getPTS (loadInst->getPointerOperand());
        for (auto it = pts.begin (); it != pts.end (); it++)
        {
            PAGNode* pagNode = *it;
            uses.insert (pagNode->value);
        }

        return;
    }

    inline ValueSet getUses(DFGNode* node) 
    {
        ValueSet defs, uses;
        llvm::Instruction* inst = node->getInstruction ();
        if (inst == nullptr) return uses;

        if (llvmParser->isLoad (inst))
        { 
            //imoplicit defition
            handleLoad (inst, uses);
        }
        else
        {
            llvmParser->getDefUse (inst, defs, uses);
        }
     
        return uses;
    }

    inline ValueSet getMinus (ValueSet& src, ValueSet& oprand)
    {
        ValueSet diff;
        set_difference(src.begin(), src.end(),
                       oprand.begin(), oprand.end(),
                       inserter(diff, diff.begin()));
        return diff;
    }

    inline void addDFGEdge (CFG *cfg, DFGNode* defNode, DFGNode* useNode, llvm::Value* def)
    {
        DFGEdge* edge = cfg->getEdge(defNode, useNode);
        if (edge == NULL)
        {
            edge = new DFGEdge(defNode, useNode);
            assert (edge != NULL);
            cfg->addEdge(edge);
            edge->edgeType = EDGE_DFG;
        }
        else
        {
            edge->edgeType |= EDGE_DFG;
        }
        edge->values.insert (def);
        
        return;
    }


    inline void buildDFG(CFG *cfg, DFASet& IN) 
    {
        // Iterate over all CFG nodes
        for (auto itNode = cfg->begin(); itNode != cfg->end(); itNode++) 
        {
            DFGNode* node = itNode->second;

            // add your code here
            ValueSet uses=getUses(node);
            for(auto val:uses)
            {
                auto it=defToNode.find(val);
                
                if(it==defToNode.end())
                {
                    continue;
                }
                for(DFGNode *defNode : it->second)
                {
                    if(IN[node].count(val) && defNode != node)
                    {
                        addDFGEdge(cfg,defNode,node,val);
                    }
                }
            }
        }
    }

    inline void performDFA(CFG *cfg) 
    {
        //1. initialize GEN and KILL, IN and OUT
        DFASet IN   = initializeSET (cfg); 
        DFASet OUT  = initializeSET (cfg);
        DFASet GEN  = initializeGEN (cfg);
        DFASet KILL = initializeKILL (cfg, GEN);

        //2 Worklist-based iteration
        // add your code here
        queue<DFGNode*> worklist;
        set<DFGNode*> visited;
        DFGNode* entry = cfg->begin()->second;
        worklist.push(entry);
        while(!worklist.empty())
        {
            DFGNode* node = worklist.front();
            worklist.pop();
            visited.insert(node);
            ValueSet old_out=OUT[node];
            // IN[node] = union of OUT[pred] for all predecessors
            ValueSet in;
            for(auto itPred=node->inEdgeBegin(); itPred!=node->inEdgeEnd(); ++itPred)
            {
                DFGNode *pred=(*itPred)->getSrcNode();
                ValueSet& outPred=OUT[pred];
                in.insert(outPred.begin(),outPred.end());
            }
            //update IN
            IN[node]=in;
            //calculate IN-KILL
            ValueSet diff=getMinus(IN[node],KILL[node]);
            OUT[node]=GEN[node];
            // OUT = GEN U (IN-KILL)
            OUT[node].insert(diff.begin(),diff.end());
            for(auto itSucc=node->outEdgeBegin();itSucc!=node->outEdgeEnd();++itSucc)
            {
                DFGNode *succ=(*itSucc)->getDstNode();
                // check not visited or OUT changed
                if(!visited.count(succ)||OUT[node]!=old_out)
                {
                    worklist.push(succ);
                }
            }
        }
        buildDFG(cfg, IN);
    }

    inline void showDFASet (string name, ValueSet& vs)
    {
        llvm::errs()<<"\n>>ValueSet: "<<name<<":";
        for (auto value : vs)
        {
            llvm::errs()<<"\n\t"<<*value;
        }
        llvm::errs()<<"\n";
    }

    inline void handleCall (CFG* callerCFG, llvm::CallBase* call, llvm::Function* callee)
    {
        CFG* calleeCFG = icfg->getCFG(callee);
        DFGNode* entryNode = calleeCFG->getEntryNode();

        // Match actual -> formal
        auto actualArgs = call->args();
        auto formalArgs = callee->args();
        auto formalIt = formalArgs.begin();

        for (unsigned i = 0; i < call->arg_size() && formalIt != formalArgs.end(); ++i, ++formalIt)
        {
            llvm::Value* actual = call->getArgOperand(i);
            llvm::Argument* formal = &(*formalIt);

            // Add edge: actual def (from call site) -> formal def (in callee entry)
            auto nodeSet = defToNode[actual];
            for (auto defIt = nodeSet.begin (); defIt != nodeSet.end(); defIt++)
            {
                DFGNode* defNode = *defIt;
                addDFGEdge(callerCFG, defNode, entryNode, formal);
            }
        }
        return;
    }

    inline void handleRet (DFGNode* callNode, llvm::CallBase* call, llvm::Function* callee)
    {
        if (call->getType()->isVoidTy())
        {
            return;
        }
        
        CFG* calleeCFG = icfg->getCFG(callee);
        for (auto calleeNodeIt = calleeCFG->begin(); calleeNodeIt != calleeCFG->end(); ++calleeNodeIt)
        {
            DFGNode* retNode = calleeNodeIt->second;
            llvm::Instruction* retInst = retNode->getInstruction();
            if (!retInst || !llvm::isa<llvm::ReturnInst>(retInst))
                continue;

            llvm::ReturnInst* ret = llvm::cast<llvm::ReturnInst>(retInst);
            llvm::Value* retVal = ret->getReturnValue();
            if (!retVal) continue;

            auto nodeSet = defToNode[retVal];
            for (auto defIt = nodeSet.begin (); defIt != nodeSet.end(); defIt++)
            {
                DFGNode* defNode = *defIt;
                addDFGEdge(calleeCFG, defNode, callNode, retVal);
            }
        }
    }

    inline set<llvm::Function*> resolveCallees(llvm::CallBase* call) 
    {
        set<llvm::Function*> callees;

        if (llvm::Function* direct = call->getCalledFunction()) 
        {
            if (!direct->isDeclaration())
            {
                callees.insert(direct);
            }         
        } 
        else 
        {
            llvm::Value* calledVal = call->getCalledOperand()->stripPointerCasts();        
            PTS pts = pta->getPTS (calledVal);
            for (auto it = pts.begin (); it != pts.end (); it++)
            {
                PAGNode* pagNode = *it;
                if (llvm::Function* func = llvm::dyn_cast<llvm::Function>(pagNode->value)) 
                {
                    if (!func->isDeclaration())
                    {
                        callees.insert(func);
                    }         
                }
            }
        }

        return callees;
    }

    inline void buildIDFG()  
    {
        for (auto itr = icfg->cfg_begin(); itr != icfg->cfg_end(); itr++)
        {
            CFG* callerCFG = itr->second;

            for (auto itNode = callerCFG->begin(); itNode != callerCFG->end(); itNode++)
            {
                DFGNode* callNode = itNode->second;
                llvm::Instruction* inst = callNode->getInstruction();

                if (!inst || !llvm::isa<llvm::CallBase>(inst))
                {
                    continue;
                }    

                llvm::CallBase* call = llvm::cast<llvm::CallBase>(inst);
                std::set<llvm::Function*> callees = resolveCallees(call);

                for (llvm::Function* callee : callees)
                {
                    if (!callee || callee->isDeclaration())
                    {
                        continue;
                    }

                    handleCall (callerCFG, call, callee);
                    handleRet (callNode, call, callee);                    
                }
            }
        }
    }
};

class DFGVisual : public GraphVis<DFGNode, DFGEdge, DFG> 
{
public:
    DFGVisual(const string& graphName, DFG* graph)
        : GraphVis<DFGNode, DFGEdge, DFG>(graphName, graph) {}

    ~DFGVisual() = default;

    inline string getNodeLabel (CFGNode *node)
    {
        if (node->isEntry ())
        {
            CFGEntryNode* enNode = (CFGEntryNode*)node;
            llvm::Function* func = enNode->getFunction ();
            string label = LLVM().getValueLabel (func);
            label += "( ";
            for (llvm::Argument &arg : func->args())
            {
                label += LLVM().getValueLabel (&arg) + " ";
            }
            label += ")";

            return label;
        }
        else if (node->isExit ())
        {
            return "exit";
        }
        else
        {
            llvm::Instruction* inst = node->getInstruction ();
            std::string instStr = LLVM().getValueLabel (inst);
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

    inline void writeEdge(CFGEdge *edge) 
    {
        string str;

        /* NodeId -> NodeId[style=solid,color=black, ,label="..."]; */
        if (edge->edgeType&EDGE_CFG)
        {
            str = "\t" + getNodeName (edge->getSrcNode()) + " -> " + getNodeName (edge->getDstNode()) +
              "[" + getEdgeAttributes (edge) + ",label=\"\"];";
            fprintf(m_File, "%s\n", str.c_str());
        }
        
        if (edge->edgeType&EDGE_DFG)
        {
            str = "\t" + getNodeName (edge->getSrcNode()) + " -> " + getNodeName (edge->getDstNode()) +
              "[color=green,label=\"\"];";
            fprintf(m_File, "%s\n", str.c_str());
        }

        return; 
     
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
        ICFG* icfg = m_Graph->getICFG();
        for (auto it = icfg->cfg_begin (), end = icfg->cfg_end (); it != end; it++)
        {
            CFG *cfg = it->second;
            writeCFGNodes (cfg);
        }
        //writeAllNodes (m_Graph);
        fprintf(m_File, "\n\n");

        // write edges
        fprintf(m_File, "\t// Define the edges\n"); 
        for (auto it = icfg->cfg_begin (), end = icfg->cfg_end (); it != end; it++)
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


#endif // _DFG_H_
