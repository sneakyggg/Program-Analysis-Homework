#ifndef _ANDERSEN_H_
#define _ANDERSEN_H_
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "pta.h"

using namespace std;

class Andersen: public PTA
{
public:
    Andersen (PAG *graph): PTA(graph), initialized (false) {} 
    ~Andersen () {}

    void runAnalysis(vector<PAGNode*>& imptNodes)
    {
        newFuncPTSs.clear ();
        for (auto it = imptNodes.begin (); it != imptNodes.end (); it++)
        {
            worklist.push (*it);
        }

        initializePTS();

        solveConstraints();

        updatePtsGraph ();
    }

private:
    bool initialized;

private:
    // 1) Initialize sets from ADDR_OF edges
    void initializePTS()
    {
        if (initialized == true)
        {
            return;
        }

        for (auto it = pag->begin (); it != pag->end (); it++) 
        {
            PAGNode *node = it->second;
            ptsMap[node] = PTS ();
        }

        for (auto it = pag->begin (); it != pag->end (); it++) 
        {
            PAGNode *node = it->second;

            for (auto itEdge = node->inEdgeBegin(); itEdge != node->inEdgeEnd(); itEdge++)
            {
                PAGEdge* edge = *itEdge;
                if (edge->cstType != CST_ADDR_OF) 
                {
                    continue;
                }

                PAGNode *src = edge->getSrcNode();
                bool changed = ptsMap[node].insert(src);
                if (changed) 
                {
                    worklist.push(node);
                }

                //cout<<"@@initializePTS: \n";
                //showPTS (src);
                //showPTS (node);
                //cout<<"\n";
            }
        }

        initialized = true;   
    }

    // 2) Propagate constraints until fixpoint
    void solveConstraints()
    {
        while (!worklist.empty()) 
        {
            PAGNode *node = worklist.front();
            worklist.pop();

            // For each outgoing edge from 'n', apply the relevant rule
            for (auto it = node->outEdgeBegin(); it != node->outEdgeEnd (); it++)
            {
                PAGEdge* outEdge = *it;
                switch (outEdge->cstType) 
                {
                    case CST_COPY:
                        handleCopyEdge(outEdge);
                        break;
                    case CST_STORE:
                        handleStoreEdge(outEdge);
                        break;
                    case CST_LOAD:
                        handleLoadEdge(outEdge);
                        break;
                    case CST_ADDR_OF:
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // 2a) Copy: PTS(dst) ⊇ PTS(src)
    void handleCopyEdge(PAGEdge *edge)
    {
        
        // add your code here
        PAGNode *src=edge->getSrcNode();
        PAGNode *dst=edge->getDstNode();
        bool changed=ptsMap[dst].unionWith(ptsMap[src]);
        if(changed)
        {
            checkAndSetFuncPtr(dst);
            worklist.push(dst);
        }
            
    }

    // 2b) Store: (*src) = dst
    //   For each object o in PTS(src), do PTS(o) ⊇ PTS(dst)
    void handleStoreEdge(PAGEdge *edge)
    {
        // add your code here
        
        PAGNode *src=edge->getSrcNode();
        PAGNode *dst=edge->getDstNode();
        //cout<<"*************"<<isPointerValue(src)<<endl;
        //cout<<"-------------"<<isPointerValue(dst)<<endl;
        if(isPointerValue(dst)){
        for (PAGNode *x : ptsMap[dst].getSet())
        {
            bool changed=ptsMap[x].unionWith(ptsMap[src]);
            if(changed)
            {
                checkAndSetFuncPtr(x);
                worklist.push(x);   
            }
        }
    }
        
    }

    // 2c) Load: dst = (*src)
    //   For each object o in PTS(src), do PTS(dst) ⊇ PTS(o)
    void handleLoadEdge(PAGEdge *edge)
    {
        
        // add your code here
        PAGNode *src=edge->getSrcNode();
        PAGNode *dst=edge->getDstNode();
        //cout<<"*************"<<isPointerValue(src)<<endl;
        //cout<<"-------------"<<isPointerValue(dst)<<endl;
        if(isPointerValue(dst)){
        for(PAGNode *x : ptsMap[src].getSet())
        {
            bool changed=ptsMap[dst].unionWith(ptsMap[x]);
            if(changed)
            {

                checkAndSetFuncPtr(dst);
                worklist.push(dst);
            }
        }
    }
        
    }

};


#endif 
