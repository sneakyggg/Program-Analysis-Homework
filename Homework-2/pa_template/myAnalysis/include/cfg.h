
#ifndef _CFG_H_
#define _CFG_H_
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "generic_graph.h"
#include "graph_visual.h"
#include "graph_test.h"
#include "graph_generator.h"
#include "llvm_wrapper.h"

using namespace std;
class CFGNode; // Forward declaration
class CFGEdge : public GenericEdge<CFGNode>
{
public:
    CFGEdge(CFGNode *s, CFGNode *d)
        : GenericEdge<CFGNode>(s, d) {}

    ~CFGEdge() {}
};

class CFGNode : public GenericNode<CFGEdge>
{
public:
    CFGNode(unsigned Id, llvm::Instruction *inst = NULL)
        : GenericNode<CFGEdge>(Id) { llvmInst = inst; }

    ~CFGNode() {}

    inline llvm::Instruction *getInstruction() { return llvmInst; }
    inline llvm::BasicBlock *getBasicBlock() { return llvmInst->getParent(); }
    virtual inline bool isEntry() { return false; }
    virtual inline bool isExit() { return false; }

private:
    llvm::Instruction *llvmInst;
};

class CFGEntryNode : public CFGNode
{
public:
    CFGEntryNode(unsigned Id, llvm::Function *func)
        : CFGNode(Id, NULL) { llvmFunc = func; }

    ~CFGEntryNode() {}

    inline bool isEntry() { return true; }
    inline llvm::Function *getFunction() { return llvmFunc; }

private:
    llvm::Function *llvmFunc;
};

class CFGExitNode : public CFGNode
{
public:
    CFGExitNode(unsigned Id)
        : CFGNode(Id, NULL) {}

    ~CFGExitNode() {}
    inline bool isExit() { return true; }
};

class CFG : public GenericGraph<CFGNode, CFGEdge>
{
public:
    CFG(unsigned initId = 1) { initNodeId = initId; }
    ~CFG() {}

    void build(llvm::Function &F)
    {
        if (F.isDeclaration())
            return;

        // Create artificial entry/exit nodes
        entryNode = new CFGEntryNode(getNextNodeId(), &F);
        assert(entryNode != NULL);
        addNode(entryNode->getId(), entryNode);
        exitNode = new CFGExitNode(getNextNodeId());
        assert(exitNode != NULL);
        addNode(exitNode->getId(), exitNode);

        queue<CFGNode *> worklist;
        map<llvm::BasicBlock *, pair<CFGNode *, CFGNode *>> visited;

        llvm::BasicBlock *entryBB = &F.getEntryBlock();
        vector<CFGNode *> entrySubgraph = getSubgraph(entryBB);
        if (!entrySubgraph.empty())
        {
            addCFGEdge(entryNode, entrySubgraph.front());
            worklist.push(entrySubgraph.back());
        }
        visited[entryBB] = make_pair(entrySubgraph.front(), entrySubgraph.back());

        while (!worklist.empty())
        {

            CFGNode *curNode = worklist.front();
            worklist.pop();

            llvm::BasicBlock *curBB = curNode->getBasicBlock();

            if (!curBB)
                continue;

            llvm::Instruction *termInst = curBB->getTerminator();
            if (!termInst)
                continue;

            if (llvm::isa<llvm::ReturnInst>(termInst))
            {

                addCFGEdge(visited[curBB].second, exitNode);
                continue;
            }

            if (llvm::isa<llvm::UnreachableInst>(termInst))
            {

                addCFGEdge(visited[curBB].second, exitNode);
                continue;
            }

            for (auto SI = llvm::succ_begin(curBB), SE = llvm::succ_end(curBB); SI != SE; ++SI)
            {
                llvm::BasicBlock *succBB = *SI;

                if (!visited.count(succBB))
                {

                    auto succSubgraph = getSubgraph(succBB);
                    if (!succSubgraph.empty())
                    {

                        visited[succBB] = make_pair(succSubgraph.front(), succSubgraph.back());

                        addCFGEdge(visited[curBB].second, succSubgraph.front());

                        worklist.push(succSubgraph.back());
                    }
                    else
                    {
                        addCFGEdge(visited[curBB].second, exitNode);
                    }
                }
                else
                {
                    addCFGEdge(visited[curBB].second, visited[succBB].first);
                }
            }
        }
    }

    inline CFGNode *getCFGNode(llvm::Instruction *inst)
    {
        auto it = instToNode.find(inst);
        if (it == instToNode.end())
        {
            return NULL;
        }

        return it->second;
    }

    inline CFGNode *getEntryNode() { return entryNode; }
    inline CFGNode *getExitNode() { return exitNode; }

private:
    map<const llvm::Instruction *, CFGNode *> instToNode;
    CFGNode *entryNode;
    CFGNode *exitNode;
    unsigned initNodeId;

private:
    inline unsigned getNextNodeId()
    {
        return getNodeNum() + initNodeId;
    }

    inline CFGNode *addCFGNode(llvm::Instruction *llvmInst)
    {
        CFGNode *node = new CFGNode(getNextNodeId(), llvmInst);
        assert(node != NULL);
        addNode(node->getId(), node);

        if (llvmInst != NULL)
        {
            instToNode[llvmInst] = node;
        }

        return node;
    }

    inline CFGEdge *addCFGEdge(CFGNode *src, CFGNode *dst)
    {
        CFGEdge *edge = new CFGEdge(src, dst);
        assert(edge != NULL);
        addEdge(edge);

        return edge;
    }

    inline vector<CFGNode *> getSubgraph(llvm::BasicBlock *BB)
    {
        vector<CFGNode *> subgraph;
        CFGNode *prevInstNode = nullptr;

        for (llvm::Instruction &I : *BB)
        {
            if (llvm::isa<llvm::DbgInfoIntrinsic>(&I) ||
                llvm::isa<llvm::DbgVariableIntrinsic>(&I))
            {
                continue;
            }

            CFGNode *instNode = addCFGNode(&I);
            subgraph.push_back(instNode);

            if (prevInstNode)
            {
                addCFGEdge(prevInstNode, instNode);
            }

            prevInstNode = instNode;
        }

        return subgraph;
    }
};

class CFGVisual : public GraphVis<CFGNode, CFGEdge, CFG>
{
public:
    CFGVisual(std::string graphName, CFG *graph)
        : GraphVis<CFGNode, CFGEdge, CFG>(graphName, graph) {}

    ~CFGVisual() {}

    inline string getNodeLabel(CFGNode *node)
    {
        if (node->isEntry())
        {
            CFGEntryNode *enNode = (CFGEntryNode *)node;
            llvm::Function *func = enNode->getFunction();
            return func->getName().str();
        }
        else if (node->isExit())
        {
            return "exit";
        }
        else
        {
            llvm::Instruction *inst = node->getInstruction();

            std::string instStr;
            llvm::raw_string_ostream instStream(instStr);
            inst->print(instStream);

            return escapeForDotLabel(instStream.str());
        }
    }

    inline string getNodeAttributes(CFGNode *node)
    {
        string str = "shape=rectangle, color=black";
        return str;
    }
};

#endif
