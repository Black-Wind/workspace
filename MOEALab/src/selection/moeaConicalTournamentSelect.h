#pragma once

#include "../global.h"
#include "moeaSelectIndex.h"
#include "../subproblem/subproblem.h"
#include "../fitness/fitness.h"

template <class MOEOT>
class moeaConicalTournamentSelect : public moeaSelectIndex
{
public:

    moeaConicalTournamentSelect(unsigned int _nPop,moeaConicalComparator<MOEOT> &_comparator):moeaSelectIndex(_nPop),comparator(_comparator){ }

    virtual unsigned int select() {
        //cout<<"TournamentSelection"<<endl;
        unsigned int ind1 = rng.uniform(this->nPop);
        unsigned int ind2;
        do
        {
            ind2 = rng.uniform(this->nPop);
        }while(ind1 == ind2);

       // cout<<"["<<ind1<<"]  ["<<ind2<<"]"<<endl;

        if(comparator.diffCompare(ind1,ind2)) {
         //   cout<<"1"<<endl;
            return ind1;
        }
        else {
           // cout<<"2"<<endl;
            return ind2;
        }
    }

    virtual void operator()(unsigned int _indexInd,vector<unsigned int> &_selectList, unsigned int _num = 2)
    {
        moeaSelectIndex::operator()(_selectList,_num);
    }

    moeaConicalComparator<MOEOT> &comparator;
};