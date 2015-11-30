#pragma once

#include "../global.h"
#include "moeaSubProblem.h"
#include "moeaSubProblemLocate.h"

class moeaVicinityInit
{
public:
    moeaVicinityInit(unsigned int _nH):nH(_nH){}
    void operator()(const vector<unsigned int> &_observe,vector<unsigned int> &neighbor)
    {
        vector<unsigned int> tmp = _observe;
        unsigned int nObj = _observe.size();
        for(unsigned int i=0;i<nObj;i++)
        {
            tmp[i] = tmp[i] + 1;
            if(tmp[i] <= nH) {
                for (unsigned int j = i + 1; j < nObj; j++) {
                    tmp[j] = tmp[j] - 1;
                    if(tmp[j] >= 0)
                        neighbor.push_back(locate.locateIndex(tmp));
                    tmp[j] = tmp[j] + 1;
                }
            }
            tmp[i] = tmp[i] - 2;
            if(tmp[i] >= 0) {
                for (unsigned int j = i + 1; j < nObj; j++) {
                    tmp[j] = tmp[j] + 1;
                    if(tmp[j] <= nH)
                        neighbor.push_back(locate.locateIndex(tmp));
                    tmp[j] = tmp[j] - 1;
                }
            }
            tmp[i] = tmp[i] + 1;
        }
    }

    vector<unsigned int> operator()(const vector<unsigned int> &_observe)
    {
        vector<unsigned int> neighbor;
        this->operator()(_observe,neighbor);
        return neighbor;
    }

    void operator() (vector<moeaSubProblem>& _subProblems) {

        unsigned int nPop = _subProblems.size();

        for(unsigned int i=0; i<nPop; i++)
        {
            this->operator()(_subProblems[i].observe,_subProblems[i].neighbor);
        }
    };

    /// My class name.
    virtual std::string className() const
    {
        return "moeaVicinityInit";
    }
    moeaSubProblemLocate locate;
    unsigned int nH;
};

