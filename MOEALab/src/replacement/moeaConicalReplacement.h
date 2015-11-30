#pragma once

#include "../global.h"
#include "../subproblem/subproblem.h"
#include "../fitness/fitness.h"
#include "../extremePoint/extremePoint.h"

/**
 * Neighbor replacement strategy that update niche neighbor .
 */

template < class MOEOT >
class moeaConicalReplacement:public moeoReplacement < MOEOT >
{
public:

    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    moeaConicalReplacement (moeaConicalComparator<MOEOT> &_comparator,moeaSubProblemMapping &_mapSubProblem,moeaNormalized<MOEOT> &_normalized) :
            comparator(_comparator),mapSubProblem(_mapSubProblem),normalized(_normalized)
    {
        de = vector<unsigned int>(100,0);
    }

    virtual void operator()(eoPop<MOEOT> &A1, eoPop<MOEOT> &A2){}
    /**
     * Replaces the first population by adding the individuals of the second one, sorting with a moeoComparator and resizing the whole population obtained.
        * @param _parents the population composed of the parents (the population you want to replace)
        * @param _offspring the offspring population
     */
    void operator () (MOEOT & _offspring,eoPop < MOEOT > &_pop)
    {
        unsigned int nPop = _pop.size();

        //auto && normOffspring = normalized(_offspring);
        auto normOffspring = normalized(_offspring);

        unsigned int index = locate(normOffspring);
        unsigned int popIndex = mapSubProblem.pIndex(index);
        unsigned int actualS;

        vector<double> normInd;

        if(mapSubProblem.check(popIndex))
            actualS = mapSubProblem.actualIndex(popIndex);
        else
        {
            normalized(_pop[popIndex],normInd);
            actualS = locate(normInd);
            mapSubProblem.setActualIndex(popIndex,actualS);
        }

        bool isReplaced = false;
        if(actualS == index)
        {
            if(normInd.size() == 0) normalized(_pop[popIndex],normInd);
            Fitness fitness;
            if(comparator(normInd,normOffspring,index,fitness))
            {
                _offspring.fitness(fitness);
                isReplaced = true;
            }
        }
        else
        {
            isReplaced = true;
        }

        if(isReplaced)
        {
            _pop[popIndex] = _offspring;
            mapSubProblem.bind(index,popIndex);
            mapSubProblem.setActualIndex(popIndex,index);
            de[index]++;
        }
    }
    vector<unsigned int> de;

protected:

    moeaSubProblemLocate locate;
    moeaConicalComparator<MOEOT> &comparator;
    moeaSubProblemMapping &mapSubProblem;
    moeaNormalized<MOEOT> &normalized;

};
