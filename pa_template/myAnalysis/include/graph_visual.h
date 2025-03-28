
#ifndef _GRAPH_VISUAL_H_
#define _GRAPH_VISUAL_H_
#include <fstream>
#include <cassert>

using namespace std;

enum
{
    E_ATTR_COLOR_BLACK=0,
    E_ATTR_COLOR_BLUE=1,
    E_ATTR_COLOR_RED=2,

    E_ATTR_COLOR_INVALID=0XFF,
};

template<class NodeTy,class EdgeTy, class GraphType> class GraphVis 
{
protected:
    FILE  *m_File;
    GraphType *m_Graph;
    string m_GraphName;
    string m_GraphLabel;

protected:
    inline void writeHeader (string graphName) 
    {
        fprintf(m_File, "digraph \"%s\"{\n", graphName.c_str());
        fprintf(m_File, "\tlabel=\"%s\";\n", getGraphLabel().c_str()); 
        fprintf(m_File, "\n\n");

        return;
    }

    inline string escapeForDotLabel(const string &input) 
    {
        std::string output;
        output.reserve(input.size());

        for (char c : input) {
            if (c == '\"') output.push_back('\\');
            output.push_back(c);
        }
        return output;
    }

    inline string getGraphLabel() 
    {
        if (m_GraphLabel != "")
        {
            return m_GraphName + " " + m_GraphLabel; 
        }

        return m_GraphName;
    }

    virtual inline string getNodeLabel(NodeTy *node) 
    {
        string str = "";
        str = "N-" + to_string (node->getId ());
        return str;
    }

    virtual inline string getNodeName(NodeTy *node) 
    {
        string str = "";
        str = "N" + to_string (node->getId ());
        return str;
    }
    
    virtual inline string getNodeAttributes(NodeTy *node) 
    {
        string str = "color=black";   
        return str;
    }

    virtual inline string getEdgeLabel(EdgeTy *edge) 
    {
        return "";
    }

    virtual inline string getEdgeAttributes(EdgeTy *edge) 
    {
        string str = "color=black";
        return str;
    }
 
    inline void writeNodes(NodeTy *Node) 
    {
        /* NodeID [color=grey,label="{NodeID: 0}"]; */
        string str;
        str = getNodeName (Node) + " [" + getNodeAttributes (Node) + 
              ",label=\"" + "[" + to_string(Node->getId()) + "]" + getNodeLabel (Node) + "\"];";

        fprintf(m_File, "\t%s\n", str.c_str());
        return;        
    }
 

    inline void writeEdge(EdgeTy *edge) 
    {
        /* NodeId -> NodeId[style=solid,color=black, ,label="..."]; */
        string str;

        str = "\t" + getNodeName (edge->getSrcNode()) + " -> " + getNodeName (edge->getDstNode()) +
              "[" + getEdgeAttributes (edge) + ",label=\"\"];";
               
        fprintf(m_File, "%s\n", str.c_str());
        return; 
     
    }

    virtual inline bool IsEdgeType (EdgeTy *edge)
    {
        return true;
    }

    virtual inline bool IsVizNode (NodeTy *node)
    {
        return true;
    }

    virtual inline bool IsVizEdge (EdgeTy *edge)
    {
        return true;
    }

public:
    GraphVis(string graphName, GraphType* graph) 
    {
        m_GraphName  = graphName;
        m_GraphLabel = "";
        
        string dotFile = graphName + ".dot";
        m_File    = fopen (dotFile.c_str(), "w");
        assert (m_File != NULL);

        m_Graph = graph;
    }

    virtual ~GraphVis()
    {
        fclose (m_File);
    }

    virtual inline void setNodeLabel(string GLabel) 
    {
        m_GraphLabel = GLabel;
        return;
    }

    inline void writeAllNodes (GraphType *g)
    {
        for (auto it = g->begin (), end = g->end (); it != end; it++)
        {
            NodeTy *node = it->second;
            if (!IsVizNode (node))
            {
                continue;
            }
            writeNodes (node);
        }
    }

    inline void writeAllEdges (GraphType *g)
    {
        for (auto it = g->begin (), end = g->end (); it != end; it++)
        {
            NodeTy *node = it->second;
            if (!IsVizNode (node))
            {
                continue;
            }

            for (auto itEdge = node->outEdgeBegin (), itEnd = node->outEdgeEnd (); itEdge != itEnd; itEdge++)
            {
                EdgeTy *edge = *itEdge;
                if (!IsVizNode (edge->getDstNode()))
                {
                    continue;
                }
                
                writeEdge (edge);
            }
        }
    }

    virtual void witeGraph () 
    {
        writeHeader(m_GraphName);

        // write nodes
        fprintf(m_File, "\t// Define the nodes\n");
        writeAllNodes (m_Graph);
        fprintf(m_File, "\n\n");

        // write edges
        fprintf(m_File, "\t// Define the edges\n");
        writeAllEdges (m_Graph);
        fprintf(m_File, "}\n");
    }   
};

#endif 
