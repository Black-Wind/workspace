#pragma once

#include "../global.h"

#include "moeaRecombination.h"

template <class MOEOT>
class moeaQuadRecombination : public moeaRecombination<MOEOT>
{
public:
    moeaQuadRecombination(moeaSelectIndex &_select,eoQuadOp < MOEOT > & _crossover, eoMonOp < MOEOT > & _mutation):moeaRecombination<MOEOT>(_select,_mutation),crossover(_crossover){}

    moeaQuadRecombination(moeaSelectIndex &_select,eoQuadOp < MOEOT > & _crossover, eoMonOp < MOEOT > & _mutation, moeaRepairOp<MOEOT> &_repair):moeaRecombination<MOEOT>(_select,_mutation,_repair),crossover(_crossover){}

    virtual MOEOT operator()(const eoPop<MOEOT>& _pop,unsigned int _indexInd)
    {
        //cout<<"recombination"<<endl;
        vector<unsigned int> selectedList;
        this->select(_indexInd, selectedList,2);

        //cout<<"selection: " <<selectedList[0]<<"\t"<<selectedList[1]<<endl;

        MOEOT offspring(_pop[ selectedList[0] ]);

        offspring.invalidate();

        //cout<<"off : "<<offspring<<endl;

        crossover(offspring,_pop[ selectedList[1] ]);

        this->mutation(offspring);

        this->repair(offspring);

        return offspring;
    }

    eoQuad2BinOp< MOEOT > crossover;
};

