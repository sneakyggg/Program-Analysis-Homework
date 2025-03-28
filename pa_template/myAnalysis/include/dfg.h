
#ifndef _DFG_H_
#define _DFG_H_
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include "generic_graph.h"
#include "graph_visual.h"
#include "graph_test.h"
#include "graph_generator.h"

using namespace std;

class DFGNode;  // Forward declaration
class DFGEdge : public GenericEdge<DFGNode> 
{
public:
    DFGEdge(DFGNode* s, DFGNode* d)
        : GenericEdge<DFGNode>(s, d) {}

    ~DFGEdge() {}
};

class DFGNode : public GenericNode<DFGEdge> 
{  
public:
    DFGNode(unsigned Id)
        : GenericNode<DFGEdge>(Id) {}
};

class DFG : public GenericGraph<DFGNode, DFGEdge> 
{
public:
    DFG() {}
    PAG (LLVM *llvmpas): llvmParser (llvmpas) {} 

    ~DFG() {}

    void build()
    {
    }

private:
    map<const llvm::Instruction*, DFGNode*> valueToNode;
    LLVM *llvmParser;
};

class DFGVisual: public GraphVis<DFGNode, DFGEdge, DFG>
{
public:
    DFGVisual(std::string graphName, DFG *graph)
        : GraphVis<DFGNode, DFGEdge, DFG>(graphName, graph) {}

    ~DFGVisual() {}
};

class DFGTest: public GraphTest<DFGNode, DFGEdge, DFG>
{
public:
    DFGTest() : GraphTest<DFGNode, DFGEdge, DFG>() {}
    ~DFGTest() {}

    void runTests()
    {
        // Add your own tests here
        testGraphDump();

        GraphTest::runTests();
    }

private:
    void testGraphDump()
    {
        GraphGenerator<DFGNode, DFGEdge, DFG> generator;
        DFG randomGraph = generator.generateRandomGraph(10);

        DFGVisual dfgVisual("dfg", &randomGraph);
        dfgVisual.witeGraph();
    }
};

#endif 
