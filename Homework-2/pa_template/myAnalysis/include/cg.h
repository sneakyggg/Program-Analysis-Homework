
#ifndef _CG_H_
#define _CG_H_
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include "generic_graph.h"
#include "graph_visual.h"
#include "graph_test.h"
#include "graph_generator.h"

using namespace std;

class CGNode; // Forward declaration
class CGEdge : public GenericEdge<CGNode>
{
public:
    CGEdge(CGNode *s, CGNode *d)
        : GenericEdge<CGNode>(s, d) {}

    ~CGEdge() {}
};

class CGNode : public GenericNode<CGEdge>
{
public:
    typedef vector<llvm::CallBase *>::iterator cs_iterator;

    CGNode(unsigned Id, llvm::Function *func = NULL)
        : GenericNode<CGEdge>(Id) { llvmFunc = func; }

    ~CGNode() {}

    llvm::Function *getLLVMFunc()
    {
        return llvmFunc;
    }

    void addCallsite(llvm::CallBase *callInst)
    {
        callsites.push_back(callInst);
    }

    cs_iterator begin() { return callsites.begin(); }
    cs_iterator end() { return callsites.end(); }

private:
    llvm::Function *llvmFunc;
    vector<llvm::CallBase *> callsites;
};

class CG : public GenericGraph<CGNode, CGEdge>
{
public:
    CG(LLVM *llvmpas = NULL) { llvmParser = llvmpas; }
    ~CG() {}

public:
    void build()
    {
        if (!llvmParser)
            return;

        for (auto it = llvmParser->func_begin(); it != llvmParser->func_end(); ++it)
        {
            llvm::Function *F = *it;
            if (F->getName().startswith("llvm.dbg."))
                continue;

            CGNode *callerNode = getCGNode(F);
            if (!callerNode)
            {
                callerNode = addCGNode(F);
                func2Nodes[F] = callerNode;
            }

            for (auto &BB : *F)
            {
                for (auto &I : BB)
                {
                    // if CallBase
                    if (auto *callInst = llvm::dyn_cast<llvm::CallBase>(&I))
                    {
                        // get callee
                        llvm::Function *callee = callInst->getCalledFunction();
                        if (!callee)
                            continue;

                        if (callee->getName().startswith("llvm.dbg."))
                            continue;
                        CGNode *calleeNode = getCGNode(callee);
                        if (!calleeNode)
                        {
                            calleeNode = addCGNode(callee);
                            func2Nodes[callee] = calleeNode;
                        }

                        //  callerNode
                        callerNode->addCallsite(callInst);

                        // add new edge
                        addCGEdge(callerNode, calleeNode);
                    }
                }
            }
        }

        set<CGNode *> visited;
        for (auto nodeItr = begin(); nodeItr != end(); nodeItr++)
        {
            CGNode *node = nodeItr->second;
            if (visited.find(node) != visited.end())
                continue;

            // BFS
            queue<CGNode *> worklist;
            worklist.push(node);

            while (!worklist.empty())
            {
                CGNode *cur = worklist.front();
                worklist.pop();

                // if already visited, skip
                if (visited.find(cur) != visited.end())
                    continue;

                // visited
                visited.insert(cur);

                for (auto edgeIt = cur->outEdgeBegin(); edgeIt != cur->outEdgeEnd(); ++edgeIt)
                {
                    CGEdge *edge = *edgeIt;
                    CGNode *succ = edge->getDstNode();
                    if (visited.find(succ) == visited.end())
                    {
                        worklist.push(succ);
                    }
                }
            }
        }
    }

    inline CGNode *getCGNode(llvm::Function *llvmFunc)
    {
        auto itr = func2Nodes.find(llvmFunc);
        if (itr == func2Nodes.end())
        {
            return NULL;
        }
        return itr->second;
    }

private:
    inline unsigned getNextNodeId()
    {
        return getNodeNum() + 1;
    }

    inline CGNode *addCGNode(llvm::Function *llvmFunc)
    {
        CGNode *node = new CGNode(getNextNodeId(), llvmFunc);
        assert(node != NULL);
        addNode(node->getId(), node);

        return node;
    }

    inline CGEdge *addCGEdge(CGNode *src, CGNode *dst)
    {
        CGEdge *edge = new CGEdge(src, dst);
        assert(edge != NULL);
        addEdge(edge);

        return edge;
    }

private:
    LLVM *llvmParser;
    map<llvm::Function *, CGNode *> func2Nodes;
};

class CGVisual : public GraphVis<CGNode, CGEdge, CG>
{
public:
    CGVisual(std::string graphName, CG *graph)
        : GraphVis<CGNode, CGEdge, CG>(graphName, graph) {}

    ~CGVisual() {}

    inline string getNodeAttributes(CGNode *node)
    {
        string str = "shape=rectangle, color=black";
        return str;
    }

    inline string getNodeLabel(CGNode *node)
    {
        llvm::Function *F = node->getLLVMFunc();

        string str = "";
        str = F->getName().str();
        return str;
    }
};

#endif
