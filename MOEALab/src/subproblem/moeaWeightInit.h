#pragma once

#include "../global.h"

#include "moeaSubProblem.h"

class moeaWeightInit
{
public:
    moeaWeightInit(unsigned int _nPop, unsigned int _nObj, unsigned int _nH):nPop(_nPop),nObj(_nObj),nH(_nH){}

    void operator() (vector<moeaSubProblem>& subProblems) {
        vector<unsigned int> coordinate(nObj, 0);
        genUniformWeight(nObj - 1, nH, coordinate, subProblems);
        coordinate.clear();
    };

    /// My class name.
    virtual std::string className() const
    {
        return "moeaWeightInit";
    }
private:

    void genUniformWeight(unsigned int i_startObj, unsigned int l_maxValue, vector<unsigned int> coordinate, vector<moeaSubProblem>& subProblems)
    {
        if (0 == i_startObj || 0 == l_maxValue)
        {
            coordinate[i_startObj] = l_maxValue;

            moeaSubProblem sop;
            sop.observe = coordinate;
            double nd = sqrt( inner_product(sop.observe.begin(),sop.observe.end(),sop.observe.begin(),0.0) );

            for (unsigned int k = 0; k < nObj; k++)
            {
                sop.weight.push_back(1.0*sop.observe[k]/nd);
            }
            subProblems.push_back(sop);
            return;
        }

        for (int i = l_maxValue; i >= 0; i--)
        {
            coordinate[i_startObj] = i;
            genUniformWeight(i_startObj - 1, l_maxValue - i, coordinate,subProblems);
        }
    }

    unsigned int nPop;
    unsigned int nObj;
    unsigned int nH;

};

