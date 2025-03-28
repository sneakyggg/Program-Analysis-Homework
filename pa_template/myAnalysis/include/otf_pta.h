#ifndef _OTF_PTA_H_
#define _OTF_PTA_H_
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "andersen.h"

using namespace std;


// on-the-fly pointer analysis
class OTFPTA
{
public:
    OTFPTA (ICFG&icfg)
    {
        wICFG = &icfg;

        wPAG  = new PAG (wICFG);
        assert (wPAG != NULL);
        wPAG->build ();
    }

    ~OTFPTA () 
    {
        delete wPAG;
    }

    void solve ()
    {
        vector<PAGNode*> initNodes = {};
        PTA *pta = new Andersen (wPAG);
        assert (pta != NULL);

        while (true)
        {
            // 1) Run your pointer analysis to populate or update points-to sets.
            pta->runAnalysis(initNodes);

            // 2) Gather newly discovered function-pointer targets.
            unordered_map<llvm::Value*, unordered_set<llvm::Function*>> fPTS = pta->getFuncPts();
            if (fPTS.size () == 0)
            {
                break;
            }

            for (auto &pair : fPTS)
            {
                llvm::Value *fpVal = pair.first; 
                const auto &pCallees = pair.second;

                // 3) Refine the ICFG with the newly discovered function pointers.
                wICFG->refine (fpVal, pCallees);

                // 4) Refine the PAG for the next iteration.
                initNodes = wPAG->refine (fpVal, pCallees);
            }   
        }

        // dump graphs
        dumpCG ();
        dumpICFG ();
        dumpPAG ();

        delete pta;
        pta = NULL;
    }

private:
    ICFG *wICFG;
    PAG  *wPAG;

private:
    inline void dumpCG ()
    {
        CGVisual vis ("w-cg", wICFG->getCG());
        vis.witeGraph();
    }

    inline void dumpICFG ()
    {
        ICFGVisual vis ("w-icfg", wICFG);
        vis.witeGraph();
    }

    inline void dumpPAG ()
    {
        PAGVis vis("w-pag", wPAG);
        vis.witeGraph();
    }
};

#endif 
