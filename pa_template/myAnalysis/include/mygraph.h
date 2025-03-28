
#ifndef _MYGRAPH_H_
#define _MYGRAPH_H_
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include "generic_graph.h"
#include "graph_visual.h"
#include "graph_test.h"
#include "graph_generator.h"

using namespace std;

class myNode;
class myEdge : public GenericEdge<myNode> 
{
public:
    myEdge(myNode* s, myNode* d):GenericEdge<myNode>(s, d) {}

    ~myEdge() {}
};


class myNode : public GenericNode<myEdge> 
{  
public:
    myNode(unsigned Id): GenericNode<myEdge>(Id) {}
};


class myGraph : public GenericGraph<myNode, myEdge> 
{
public:
    myGraph() {} 
    ~myGraph() {}
};


class myGraphVisual: public GraphVis <myNode, myEdge, myGraph>
{
public:
    myGraphVisual (string graphName, myGraph *graph)
        :GraphVis <myNode, myEdge, myGraph>(graphName, graph) {}

    ~myGraphVisual () {}
};

class myGraphTest: public GraphTest <myNode, myEdge, myGraph>
{
public:
    myGraphTest (): GraphTest <myNode, myEdge, myGraph>() {}
    ~myGraphTest () {}

    void runTests ()
    {
        // add your own test here
        testGraphDump ();

        GraphTest::runTests ();
    }

private:
    void testGraphDump ()
    {
        GraphGenerator<myNode, myEdge, myGraph> generator;
        myGraph randomGraph = generator.generateRandomGraph(10);

        myGraphVisual myGV ("mygraph", &randomGraph);
        myGV.witeGraph ();
    }
    
};
#endif 
