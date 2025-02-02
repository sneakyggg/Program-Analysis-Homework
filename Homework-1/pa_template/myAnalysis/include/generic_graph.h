#ifndef _GENERIC_GRAPH_H_
#define _GENERIC_GRAPH_H_
#include <set>
#include <map>

using namespace std;

template<class NodeTy> class GenericEdge 
{    
private:
    NodeTy* m_SrcNode;
    NodeTy* m_DstNode;

public:

    GenericEdge(NodeTy* s, NodeTy* d): m_SrcNode(s),m_DstNode(d)
    {

    }

    virtual ~GenericEdge() 
    {
    }

    inline unsigned getSrcID() const 
    {
        return m_SrcNode->getId();
    }
    
    inline unsigned getDstID() const 
    {
        return m_DstNode->getId();
    }
    NodeTy* getSrcNode() const 
    {
        return m_SrcNode;
    }
    
    NodeTy* getDstNode() const 
    {
        return m_DstNode;
    }

    inline bool operator== (const GenericEdge<NodeTy>* rhs) const 
    {
        return (rhs->getSrcID() == this->getSrcID() &&
                rhs->getDstID() == this->getDstID());
    }

    typedef struct 
    {
        bool operator()(const GenericEdge<NodeTy>* lhs, const GenericEdge<NodeTy>* rhs) const 
        {
            if (lhs->getSrcID() != rhs->getSrcID())
            {
                return lhs->getSrcID() < rhs->getSrcID();
            }
            else
            {
                return lhs->getDstID() < rhs->getDstID();
            }
        }
    } EqualGEdge;
};


template<class EdgeTy> class GenericNode 
{

public:
    typedef std::set<EdgeTy*, typename EdgeTy::EqualGEdge> T_GEdgeSet;
    typedef typename T_GEdgeSet::iterator iterator;

private:
    unsigned m_Id;

    T_GEdgeSet m_InEdgeSet;  
    T_GEdgeSet m_OutEdgeSet;  

public:
    GenericNode(unsigned id): m_Id(id) 
    {
    }

    virtual ~GenericNode() 
    {        
        release();
    }

    inline void release()
    {
        for (auto in = inEdgeBegin (), end = inEdgeEnd (); in != end; in++)
        {
            EdgeTy *edge = *in;
            delete edge;      
        }
        m_InEdgeSet.clear();
        m_OutEdgeSet.clear();
    }

    inline unsigned getId() const
    {
        return m_Id;
    }

    inline iterator outEdgeBegin()
    {
        return m_OutEdgeSet.begin();
    }
    
    inline iterator outEdgeEnd() 
    {
        return m_OutEdgeSet.end();
    }
    
    inline iterator inEdgeBegin() 
    {
        return m_InEdgeSet.begin();
    }
    
    inline iterator inEdgeEnd() 
    {
        return m_InEdgeSet.end();
    }

    inline bool addIncomingEdge(EdgeTy* inEdge)
    {
        return m_InEdgeSet.insert(inEdge).second;
    }
    
    inline bool addOutgoingEdge(EdgeTy* outEdge) 
    {
        return m_OutEdgeSet.insert(outEdge).second;
    }

    inline void rmIncomingEdge(EdgeTy* inEdge) 
    {
        iterator it = m_InEdgeSet.find(inEdge);
        if(it == m_InEdgeSet.end())
        {
            return;
        }

        m_InEdgeSet.erase(inEdge);
        return;
    }
    
    inline void rmOutgoingEdge(EdgeTy* outEdge) 
    {
        iterator it = m_OutEdgeSet.find(outEdge);
        if(it == m_OutEdgeSet.end())
        {
            return;
        }

        m_OutEdgeSet.erase(outEdge);
        return;
    }
};

template<class NodeTy,class EdgeTy> class GenericGraph 
{

public:
    typedef map <unsigned, NodeTy*> T_IDToNodeMap;   
    typedef typename T_IDToNodeMap::iterator node_iterator;

protected:
    unsigned m_NodeNum;
    unsigned m_EdgeNum;
    T_IDToNodeMap m_IDToNodeMap;
    
public:
    
    GenericGraph()
    {
        m_NodeNum = 0;
        m_EdgeNum = 0;
    }

    virtual ~GenericGraph()
    {       
        for (auto I = m_IDToNodeMap.begin(), E = m_IDToNodeMap.end(); I != E; ++I)
        {
            delete I->second;
        }      
    }

    inline node_iterator begin() 
    {
        return m_IDToNodeMap.begin();
    }
    
    inline node_iterator end() 
    {
        return m_IDToNodeMap.end();
    }

    inline void addNode(unsigned id, NodeTy* node) 
    {
        m_IDToNodeMap[id] = node;
        m_NodeNum++;
    }

    inline unsigned getNodeNum() 
    {
        return m_NodeNum;
    }

    inline unsigned getEdgeNum() 
    {
        return m_EdgeNum;
    }

    inline bool addEdge(EdgeTy* edge)
    {
        if (edge->getDstNode()->addIncomingEdge(edge))
        {
            edge->getSrcNode()->addOutgoingEdge(edge);
            m_EdgeNum++;

            return true;
        }

        return false;
    }

    inline void rmEdge(EdgeTy* edge)
    {
        edge->getDstNode()->rmIncomingEdge(edge);
        edge->getSrcNode()->rmOutgoingEdge(edge);
            
        m_EdgeNum--;
        delete edge;
        return;
    }
};

#endif 
