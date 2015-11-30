#pragma once

#include "../global.h"

#include "../selection/selection.h"
#include "moeaRepairOp.h"

template <class MOEOT>
class moeaRecombination
{
public:
    moeaRecombination(moeaSelectIndex &_select, eoMonOp < MOEOT > & _mutation):select(_select), mutation(_mutation), repair(defaultRepairOp){}

    moeaRecombination(moeaSelectIndex &_select, eoMonOp < MOEOT > & _mutation, moeaRepairOp<MOEOT> &_repair):select(_select), mutation(_mutation), repair(_repair){}

    virtual MOEOT operator()(const eoPop<MOEOT>& _pop,unsigned int _indexInd) =0;

    moeaSelectIndex &select;
    eoMonOp<MOEOT> &mutation;
    moeaRepairOp<MOEOT> defaultRepairOp;
    moeaRepairOp<MOEOT> &repair;
};

