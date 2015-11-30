#pragma once

#include "../global.h"
#include "../extremePoint/extremePoint.h"
#include "../subproblem/subproblem.h"

template <class MOEOT>
class moeaConicalComparator
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;
    moeaConicalComparator(eoPop<MOEOT> &_pop,vector<moeaSubProblem> &_subProblems,moeaSubProblemMapping &_mapSubProblem,moeaNormalized<MOEOT> &_normalized,ObjectiveVector &_pRef):pop(_pop),subProblems(_subProblems),mapSubProblem(_mapSubProblem),normalized(_normalized),pRef(_pRef){}

    virtual bool operator()(const vector<double> &_vec1,const vector<double> &_vec2,unsigned int _index,Fitness &_finalFitness) = 0;

    virtual double diffFitness(unsigned int _ind)=0;

    virtual double diffCompare(unsigned int _ind1, unsigned int _ind2)
    {
        return diffFitness(_ind1) > diffFitness(_ind2);
    }

    moeaNormalized<MOEOT> &normalized;
    vector<moeaSubProblem> &subProblems;
    eoPop<MOEOT> &pop;
    ObjectiveVector &pRef;
    moeaSubProblemMapping &mapSubProblem;
    moeaSubProblemLocate locate;
};