#pragma once

#include "../global.h"
#include "../subproblem/subproblem.h"
#include "moeaSelectIndex.h"

class moeaDiffSelect : public moeaSelectIndex
{
public:
    moeaDiffSelect(unsigned int _nPop, vector<moeaSubProblem> &_subProblems):moeaSelectIndex(_nPop),subProblems(_subProblems)
    {
        de = vector<unsigned int>(_nPop,0);
    }

    virtual unsigned int select(unsigned int _indexInd)
    {
        return rng.choice(subProblems[_indexInd].neighbor);
    }

    virtual void operator()(unsigned int _indexInd,vector<unsigned int> &_selectList, unsigned int _num = 2)
    {
        _selectList.push_back(_indexInd);

        unsigned int count = 1;
        bool type = rng.flip();
        unsigned int p;
        while(count < _num)
        {
            p = (type ? select(_indexInd) : moeaSelectIndex::select());

            bool flag = true;
            for(unsigned int i = 0; i<_selectList.size(); i++)
            {
                if(_selectList[i]==p) // p is in the list
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                de[p]++;
                _selectList.push_back(p);
                count++;
            }
        }
    }

    vector<moeaSubProblem> &subProblems;
    vector<unsigned int> de;
};


