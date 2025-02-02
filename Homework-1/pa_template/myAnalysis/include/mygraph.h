
#ifndef _MYGRAPH_H_
#define _MYGRAPH_H_
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
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
    myEdge(myNode *s, myNode *d) : GenericEdge<myNode>(s, d) {}

    ~myEdge() {}
};

class myNode : public GenericNode<myEdge>
{
public:
    myNode(unsigned Id) : GenericNode<myEdge>(Id) {}
};

class myGraph : public GenericGraph<myNode, myEdge>
{
public:
    myGraph() {}
    ~myGraph() {}
    static myNode *getEntry(myGraph &graph)
    {
        myNode *entry = nullptr;
        for (auto nodeIt = graph.begin(); nodeIt != graph.end(); ++nodeIt)
        {
            myNode *node = nodeIt->second;

            if (node->inEdgeBegin() == node->inEdgeEnd())
            {
                //cout << "The entry is: " << nodeIt->first << endl;
                entry = node;
                return entry;
            }
        }
        return entry;
    }

    static myNode *getExit(myGraph &graph)
    {

        myNode *exit = nullptr;
        for (auto nodeIt = graph.begin(); nodeIt != graph.end(); ++nodeIt)
        {
            myNode *node = nodeIt->second;

            if (node->outEdgeBegin() == node->outEdgeEnd())
            {
                //cout << "The exit is: " << nodeIt->first << endl;
                exit = node;
                return exit;
            }
        }
        return exit;
    }

    myGraph *operator+(myGraph &graph)
    {
        /*
        cout << this->getNodeNum() << endl;
        cout << this->getEdgeNum() << endl;
        cout << graph.getNodeNum() << endl;
        cout << graph.getEdgeNum() << endl;
        */
        myNode *G1_exit = getExit(*this);
        myNode *G2_entry = getEntry(graph);

        if (!G1_exit || !G2_entry)
        {
            cerr << "Error" << endl;
            return this;
        }

        // add node
        unsigned int i = this->getNodeNum();
        unsigned int j = graph.getNodeNum();
        unsigned int k = 0;
        myNode *newnode[j];
        for (auto nodeIt = graph.begin(); nodeIt != graph.end(); ++nodeIt)
        {
            myNode *node = nodeIt->second;
            newnode[k] = new myNode(++i);
            this->addNode(newnode[k]->getId(), newnode[k]);
            k++;
        }

        // add edge
        for (auto nodeIt = graph.begin(); nodeIt != graph.end(); ++nodeIt)
        {
            myNode *node = nodeIt->second;
            for (auto edgeIt = node->outEdgeBegin(); edgeIt != node->outEdgeEnd(); ++edgeIt)
            {
                myEdge *edge = *edgeIt;
                unsigned int srcid = edge->getSrcNode()->getId();
                unsigned int dstid = edge->getDstNode()->getId();
                myEdge *newedge = new myEdge(newnode[srcid - 1], newnode[dstid - 1]);
                this->addEdge(newedge);
            }
            for (auto edgeIt = node->inEdgeBegin(); edgeIt != node->inEdgeEnd(); ++edgeIt)
            {
                myEdge *edge = *edgeIt;
                unsigned int srcid = edge->getSrcNode()->getId();
                unsigned int dstid = edge->getDstNode()->getId();
                this->addEdge(new myEdge(newnode[srcid - 1], newnode[dstid - 1]));
            }
        }
        // add the exit of G1 to the entry of G2
        myEdge *edge = new myEdge(G1_exit, newnode[G2_entry->getId() - 1]);
        this->addEdge(edge);
        /*
        cout << this->getNodeNum() << endl;
        cout << this->getEdgeNum() << endl;
        */
        return this;
    }

    static myNode *getNodeById(unsigned id, myGraph &graph)
    {

        for (auto it = graph.begin(); it != graph.end(); ++it)
        {
            myNode *node = it->second;
            if (node->getId() == id)
            {
                return node;
            }
        }
        return nullptr;
    }

    bool operator==(myGraph &graph)
    {
        // check nodes number and edges number of G1 and G2
        if (this->getNodeNum() != graph.getNodeNum() || this->getEdgeNum() != graph.getEdgeNum())
        {
            return false;
        }

        vector<unsigned> nodes1, nodes2;
        for (auto it = this->begin(); it != this->end(); ++it)
            nodes1.push_back(it->first);
        for (auto it = graph.begin(); it != graph.end(); ++it)
            nodes2.push_back(it->first);
        sort(nodes2.begin(), nodes2.end());

        // check if there is a mapping of nodes and edges:
        // for nodes:  f(nodes_1 in G1)->nodes_2 in G2
        // for edges:  f(edges_1 in G1)->edges_2 in G2
        do
        {
            map<unsigned, unsigned> nodeMapping;
            for (size_t i = 0; i < nodes1.size(); i++)
            {
                nodeMapping[nodes1[i]] = nodes2[i];
            }

            bool isMatch = true;
            for (auto it = this->begin(); it != this->end(); ++it)
            {
                myNode *v1 = it->second;
                for (auto edgeIt = v1->outEdgeBegin(); edgeIt != v1->outEdgeEnd(); ++edgeIt)
                {
                    myNode *src = (*edgeIt)->getSrcNode();
                    myNode *dst = (*edgeIt)->getDstNode();
                    unsigned mappedSrc = nodeMapping[src->getId()];
                    unsigned mappedDst = nodeMapping[dst->getId()];

                    myNode *mappedNode = graph.getNodeById(mappedSrc, graph);
                    bool found = false;
                    for (auto edgeIt2 = mappedNode->outEdgeBegin(); edgeIt2 != mappedNode->outEdgeEnd(); ++edgeIt2)
                    {
                        if ((*edgeIt2)->getDstNode()->getId() == mappedDst)
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        isMatch = false;
                        break;
                    }
                }
            }
            if (isMatch)
            {
                return true;
            }
        } while (next_permutation(nodes1.begin(), nodes1.end()));
        return false;
    }

    static void findAllPaths(myGraph &graph)
    {
        vector<vector<myNode *>> allPaths;
        myNode *start = getEntry(graph);
        if (!start)
            return;
        myNode *end = getExit(graph);
        stack<pair<myNode *, vector<myNode *>>> s;
        unordered_set<myNode *> visited;
        s.push({start, {start}});
        //DFS 
        while (!s.empty())
        {
            pair<myNode*,vector<myNode*>> topElement = s.top();
            s.pop();
            myNode* node=topElement.first;
            vector<myNode*> path=topElement.second;

            visited.insert(node);
            bool hasNext = false;
            for (auto edgeIt = node->outEdgeBegin(); edgeIt != node->outEdgeEnd(); ++edgeIt)
            {
                myNode *nextNode = ((*edgeIt)->getDstNode());
                if(visited.find(nextNode)==visited.end())
                {
                    vector<myNode*> newPath=path;
                    newPath.push_back(nextNode);
                    s.push({nextNode,newPath});
                    hasNext=true;
                }
            }
            if(!hasNext)
            {
                allPaths.push_back(path);
            }
            visited.erase(node);
        }
        
        // Print all non-cycle paths
        for(const auto& path : allPaths)
        {
            for(size_t i=0;i<path.size();++i)
            {
                cout<<path[i]->getId();
                if(i!=path.size()-1)
                cout<<" -> ";
            }
            cout<<endl;
        }
        
    }
};

class myGraphVisual : public GraphVis<myNode, myEdge, myGraph>
{
public:
    myGraphVisual(string graphName, myGraph *graph)
        : GraphVis<myNode, myEdge, myGraph>(graphName, graph) {}

    ~myGraphVisual() {}
};

class myGraphTest : public GraphTest<myNode, myEdge, myGraph>
{
public:
    myGraphTest() : GraphTest<myNode, myEdge, myGraph>() {}
    ~myGraphTest() {}

    void runTests()
    {

        // Generate two random graph
        GraphGenerator<myNode, myEdge, myGraph> generator;
        myGraph G1 = generator.generateRandomGraph(10);
        myGraph G2 = generator.generateRandomGraph(4);
        // Dump G1 and G2
        testGraphDump("G1", G1);
        testGraphDump("G2", G2);
        // Test getEntry and getExit
        cout<<"The entry of G1 is: "<<myGraph::getEntry(G1)->getId()<<endl;
        cout<<"The exit of G1 is: "<<myGraph::getExit(G1)->getId()<<endl;
        cout<<"The entry of G2 is: "<<myGraph::getEntry(G2)->getId()<<endl;
        cout<<"The exit of G2 is: "<<myGraph::getExit(G1)->getId()<<endl;
        // Overload operator '+'
        myGraph *G3 = G1 + G2;
        // Dump G3 to check if correct
        // Check G1.dot.png, G2.dot.png, G3.dot.png
        testGraphDump("G3", *G3);
        // Overload operator '='
        cout << (G1 == G1) << endl;
        cout << (G1 == G2) << endl;
        cout << (G2 == G2) << endl;
        // Print all non-cycle paths
        myGraph::findAllPaths(G2);
    }


private:
    void testGraphDump(string name, myGraph &randomGraph)
    {
        myGraphVisual myGV(name, &randomGraph);
        myGV.witeGraph();
    }
};

#endif
