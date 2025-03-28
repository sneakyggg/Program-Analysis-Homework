#ifndef __GRAPH_TEST_H__
#define __GRAPH_TEST_H__

#include <iostream>
#include <cassert>

using namespace std;

template <typename NodeType, typename EdgeType, typename GraphType>
class GraphTest 
{
public:
    virtual void runTests() 
    {
        testNodeCreation();
        testEdgeCreation();
        testAddNode();
        testAddEdge();
        testGraphStructure();
    }

private:
    void testNodeCreation() 
    {
        cout << "Running testNodeCreation..." << endl;
        NodeType node1(1);
        NodeType node2(2);

        // Verify node IDs
        assert(node1.getId() == 1);
        assert(node2.getId() == 2);
        cout << "testNodeCreation passed!" << endl;
    }

    void testEdgeCreation() 
    {
        cout << "Running testEdgeCreation..." << endl;
        NodeType node1(1);
        NodeType node2(2);

        // Create an edge
        EdgeType edge(&node1, &node2);

        // Verify edge source and destination
        assert(edge.getSrcNode() == &node1);
        assert(edge.getDstNode() == &node2);
        cout << "testEdgeCreation passed!" << endl;
    }

    void testAddNode() 
    {
        cout << "Running testAddNode..." << endl;
        GraphType graph;
        NodeType* node1 = new NodeType(1);
        NodeType* node2 = new NodeType(2);

        graph.addNode(node1->getId(), node1);
        graph.addNode(node2->getId(), node2);

        // Verify node count
        assert(graph.getNodeNum() == 2);

        // Verify nodes exist
        assert(graph.begin()->second == node1);
        cout << "testAddNode passed!" << endl;
    }

    void testAddEdge() 
    {
        cout << "Running testAddEdge..." << endl;
        GraphType graph;
        NodeType* node1 = new NodeType(1);
        NodeType* node2 = new NodeType(2);
        graph.addNode(node1->getId(), node1);
        graph.addNode(node2->getId(), node2);

        EdgeType* edge = new EdgeType(node1, node2);
        assert(graph.addEdge(edge));

        // Verify edge count
        assert(graph.getEdgeNum() == 1);
        cout << "testAddEdge passed!" << endl;
    }

    void testGraphStructure() 
    {
        cout << "Running testGraphStructure..." << endl;
        GraphType graph;

        // Add nodes
        NodeType* node1 = new NodeType(1);
        NodeType* node2 = new NodeType(2);
        NodeType* node3 = new NodeType(3);
        graph.addNode(node1->getId(), node1);
        graph.addNode(node2->getId(), node2);
        graph.addNode(node3->getId(), node3);

        // Add edges
        EdgeType* edge1 = new EdgeType(node1, node2);
        EdgeType* edge2 = new EdgeType(node2, node3);
        EdgeType* edge3 = new EdgeType(node1, node3);
        graph.addEdge(edge1);
        graph.addEdge(edge2);
        graph.addEdge(edge3);

        // Verify node and edge counts
        assert(graph.getNodeNum() == 3);
        assert(graph.getEdgeNum() == 3);

        // Verify edges
        assert(node1->outEdgeBegin() != node1->outEdgeEnd());
        assert(node2->inEdgeBegin() != node2->inEdgeEnd());

        cout << "testGraphStructure passed!" << endl;
    }
};


#endif