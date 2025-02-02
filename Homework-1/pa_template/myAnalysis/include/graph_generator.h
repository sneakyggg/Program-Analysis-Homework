#ifndef __GRAPH_GENERATOR_H__
#define __GRAPH_GENERATOR_H__

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename NodeType, typename EdgeType, typename GraphType>
class GraphGenerator 
{
public:
    GraphType generateRandomGraph(unsigned nodeCount) 
    {
        srand(static_cast<unsigned>(time(nullptr)));

        GraphType graph;

        for (unsigned i = 1; i <= nodeCount; ++i) 
        {
            NodeType* node = new NodeType(i);
            graph.addNode(i, node);
        }

        NodeType* entryNode = graph.begin()->second;
        NodeType* exitNode = graph.begin()->second;
        auto exitIt = graph.begin();
        advance(exitIt, nodeCount - 1);
        exitNode = exitIt->second;

        for (unsigned i = 1; i < nodeCount; ++i) 
        {
            NodeType* srcNode = graph.begin()->second;
            NodeType* dstNode = graph.begin()->second;
            auto srcIt = graph.begin();
            auto dstIt = graph.begin();
            advance(srcIt, i - 1);
            advance(dstIt, i);
            srcNode = srcIt->second;
            dstNode = dstIt->second;

            EdgeType* edge = new EdgeType(srcNode, dstNode);
            graph.addEdge(edge);
        }

        unsigned extraEdges = rand() % (nodeCount * 2);
        for (unsigned i = 0; i < extraEdges; ++i) 
        {
            unsigned srcId = getRandomNodeId(nodeCount);
            unsigned dstId = getRandomNodeId(nodeCount);

            if (srcId != dstId && srcId != nodeCount && dstId != 1) 
            {
                NodeType* srcNode = graph.begin()->second;
                NodeType* dstNode = graph.begin()->second;
                auto srcIt = graph.begin();
                auto dstIt = graph.begin();
                advance(srcIt, srcId - 1);
                advance(dstIt, dstId - 1);
                srcNode = srcIt->second;
                dstNode = dstIt->second;

                EdgeType* edge = new EdgeType(srcNode, dstNode);
                if (!graph.addEdge(edge)) 
                {
                    delete edge;
                }
            }
        }

        return graph;
    }

private:
    unsigned getRandomNodeId(unsigned nodeCount) 
    {
        return (rand() % nodeCount) + 1;
    }
};

#endif