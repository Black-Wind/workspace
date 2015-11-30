#pragma once

#include "../global.h"
#include "moeaSubProblem.h"

class moeaNeighborhoodInit
{
public:

    moeaNeighborhoodInit(unsigned int _nNiche):nNiche(_nNiche){}

    void operator() (vector<moeaSubProblem>& _subProblems) {

        unsigned int nPop = _subProblems.size();
        vector<double> x(nPop,0);
        vector<unsigned int> idx(nPop,0);
        eoQuadDistance< vector<double> > distance;

        for(unsigned int i=0; i<nPop; i++)
        {
            for(unsigned int j=0; j<nPop; j++)
            {
                x[j]    = distance(_subProblems[i].weight,_subProblems[j].weight);
                idx[j]  = j;
            }

            minNSort(x,idx,nPop,nNiche);

            for(unsigned int k=0; k < nNiche; k++)
                _subProblems[i].neighbor.push_back(idx[k]);
        }
        x.clear();
        idx.clear();
    };

    void minNSort(vector<double>& _x, vector<unsigned int>& _idx, unsigned int _nSize,unsigned  int _nSelect)
    {
        unsigned int selectIndex;
        for(unsigned int i=0;i<_nSelect;i++)
        {
            selectIndex = i;
            for(unsigned int j = i+1;j<_nSize;j++)
            {
                if(_x[j] < _x[selectIndex])
                {
                    selectIndex = j;
                }
            }
            if(i != selectIndex)
            {
                double temp = _x[selectIndex];
                _x[selectIndex] = _x[i];
                _x[i] = temp;
                temp = _idx[selectIndex];
                _idx[selectIndex] = _idx[i];
                _idx[i] = temp;
            }
        }
    }

    /// My class name.
    virtual std::string className() const
    {
        return "moeaNeighborhoodInit";
    }
private:

    unsigned int nNiche;

};

