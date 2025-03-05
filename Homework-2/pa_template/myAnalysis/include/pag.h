#ifndef _PAG_H_
#define _PAG_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include "generic_graph.h"
#include "graph_visual.h"
#include "graph_test.h"
#include "graph_generator.h"
#include "llvm_wrapper.h"

using namespace std;

// Forward declarations
class PAGNode;

// PAGEdge: Inherit from GenericEdge with NodeTy = PAGNode.
class PAGEdge : public GenericEdge<PAGNode> 
{
public:
    PAGEdge (PAGNode* s, PAGNode* d)
      : GenericEdge<PAGNode>(s, d) { }
};


// PAGNode: Inherit from GenericNode with EdgeTy = PAGEdge.
// We add a Label field for storing node-specific information.
class PAGNode : public GenericNode<PAGEdge> 
{
public:
    string nodeLabel;
    PAGNode (unsigned id)
      : GenericNode<PAGEdge> (id) { }
    
    PAGNode(unsigned id, const string &label)
      : GenericNode<PAGEdge>(id), nodeLabel(label) { }
};


// PAG: Our graph type; inherit from GenericGraph using PAGNode and PAGEdge.
class PAG : public GenericGraph<PAGNode, PAGEdge> 
{
public:
    PAG () {llvmParser = NULL;} 
    PAG (LLVM *llvmpas): llvmParser (llvmpas) {} 
    ~PAG () {}

public:
    void build()
    {
        // Pre-populate globals.
        addGlobalNode ();

        // Now add edges for each instruction's operands.
        for (auto fIt = llvmParser->func_begin(); fIt != llvmParser->func_end(); ++fIt)
        {
            llvm::Function *F = *fIt;
            if (F->isDeclaration())
                continue;
            
            // Pre-populate function arguments.
            addFuncArgNode (F);

            set<llvm::BasicBlock*> visited;
            queue<llvm::BasicBlock*> worklist;

            llvm::BasicBlock *entry = &F->getEntryBlock();
            worklist.push(entry);
            visited.insert(entry);

            while (!worklist.empty())
            {
                llvm::BasicBlock *BB = worklist.front();
                worklist.pop();

                // Process each instruction in the basic block.
                for (llvm::Instruction &I : *BB)
                {
                    if (!llvm::dyn_cast<llvm::StoreInst>(&I))
                    {
                        PAGNode* def = addValueNode (&I);
                        if (def == NULL)
                        {
                            continue;
                        }
                        llvm::errs ()<<I<<" is defined!\n";

                        for (unsigned op = 0, numOps = I.getNumOperands(); op < numOps; ++op)
                        {
                            llvm::Value* operand = I.getOperand(op);
                            if (llvm::isa<llvm::Constant>(operand))
                                continue;

                            PAGNode* use = getValueNode (operand);
                            if (use == NULL)
                            {
                                continue;
                            }

                            PAGEdge* edge = new PAGEdge(use, def);
                            addEdge(edge);
                            llvm::errs ()<<"@Add edge from " <<*operand<<" to "<<I<<"\n";
                        }
                    }
                    else
                    {
                        llvm::errs ()<<I<<"\n";

                        llvm::Value* op0 = I.getOperand(0);
                        if (llvm::isa<llvm::Constant>(op0))
                            continue;
                        llvm::Value* op1 = I.getOperand(1);

                        PAGNode* def = getValueNode (op1);
                        PAGNode* use = getValueNode (op0);

                        PAGEdge* edge = new PAGEdge(use, def);
                        addEdge(edge); 
                        llvm::errs ()<<"@Add edge from " <<*op0<<" to "<<*op1<<"\n";
                    }
                }

                for (llvm::BasicBlock *Succ : llvm::successors(BB))
                {
                    if (visited.find(Succ) == visited.end()) {
                        visited.insert(Succ);
                        worklist.push(Succ);
                    }
                }
            }
        }
    }

private:
    inline unsigned getNextNodeId () 
    {
        return getNodeNum() + 1;
    }

    inline PAGNode* addValueNode (llvm::Value* val)
    {
        unsigned nodeId = getNextNodeId();
        string label = getValueLabel(val);
        if (label.find (".dbg.") != string::npos)
        {
            return NULL;
        }

        PAGNode* valNode = new PAGNode(nodeId, label);
        assert (valNode != NULL);
        addNode(nodeId, valNode);
        valueToNode[val] = valNode;

        return valNode;
    }

    inline PAGNode* getValueNode (llvm::Value* val)
    {
        auto it = valueToNode.find(val);
        if (it != valueToNode.end())
        {
            return it->second;
        }

        return NULL;
    }

    inline void addGlobalNode ()
    {
        for (auto it = llvmParser->gv_begin (); it != llvmParser->gv_end (); it++)
        {
            llvm::GlobalVariable *gv = *it;

            addValueNode (gv);
        }
    }

    inline void addFuncArgNode (llvm::Function *F)
    {
        for (llvm::Argument &arg : F->args()) 
        {
             addValueNode (&arg);
        }
    }

    inline string getValueLabel(const llvm::Value* V) 
    {
        return llvmParser->getValueLabel (V);
    }

private:
    map<const llvm::Value*, PAGNode*> valueToNode;
    LLVM *llvmParser;
};



// PAGVis: A DOT generator for our PAG (constraint graph).
// Inherits from the template GraphVis using our PAG types.
class PAGVis: public GraphVis<PAGNode, PAGEdge, PAG>
{
public:
    PAGVis (string graphName, PAG *graph)
        : GraphVis<PAGNode, PAGEdge, PAG>(graphName, graph) {}

    ~PAGVis () {}

    inline string getNodeLabel(PAGNode *node) 
    {
        return node->nodeLabel;
    }
};



// PAGTest: Test cases for our PAG (constraint graph).
// Inherits from the template GraphTest using our PAG types.
class PAGTest: public GraphTest<PAGNode, PAGEdge, PAG>
{
public:
    PAGTest () : GraphTest<PAGNode, PAGEdge, PAG> () {}
    ~PAGTest () {}

    void runTests ()
    {
        // Add your own test here.
        PAGtest1 ();

        GraphTest<PAGNode, PAGEdge, PAG>::runTests();
    }

private:
    void PAGtest1 ()
    {
        PAG pag;
        
        PAGNode* node1 = new PAGNode(1);
        PAGNode* node2 = new PAGNode(2);
        PAGNode* node3 = new PAGNode(3);
        
        pag.addNode(1, node1);
        pag.addNode(2, node2);
        pag.addNode(3, node3);
        
        PAGEdge* edge1 = new PAGEdge(node1, node2);
        PAGEdge* edge2 = new PAGEdge(node2, node3);
        PAGEdge* edge3 = new PAGEdge(node1, node3);
        
        pag.addEdge(edge1);
        pag.addEdge(edge2);
        pag.addEdge(edge3);
        
        PAGVis vis("PAGTestGraph", &pag);
        vis.witeGraph();
    }
};

#endif
