#pragma once

#include "../global.h"
#include "moeaRecombination.h"

template <class MOEOT>
class moeaDiffRecombination : public moeaRecombination<MOEOT>
{
public:
    moeaDiffRecombination(moeaSelectIndex &_select,moeaDiffXover<MOEOT> &_crossover,eoMonOp < MOEOT > & _mutation):moeaRecombination<MOEOT>(_select,_mutation),crossover(_crossover),type(3){}

    moeaDiffRecombination(moeaSelectIndex &_select,moeaDiffXover<MOEOT> &_crossover, eoMonOp < MOEOT > & _mutation, moeaRepairOp<MOEOT> &_repair):moeaRecombination<MOEOT>(_select,_mutation,_repair),crossover(_crossover),type(3){}

    virtual MOEOT operator()(const eoPop<MOEOT>& _pop,unsigned int _indexInd)
    {
        vector<unsigned int> selectedList;
        this->select(_indexInd, selectedList,type);

        MOEOT offspring = _pop[selectedList[0]];
        offspring.invalidate();

        if(type == 3)
            crossover(offspring,_pop[selectedList[1]],_pop[selectedList[2]]);
        else if(type == 4)
            crossover(offspring,_pop[selectedList[1]],_pop[selectedList[2]],_pop[selectedList[3]]);

        this->mutation(offspring);

        this->repair(offspring);

        return offspring;
    }

    void setupType(unsigned int _type)
    {
        if(_type == 3 || _type == 4)
            type = _type;
    }


    moeaDiffXover< MOEOT > &crossover;
    unsigned int type;
};


