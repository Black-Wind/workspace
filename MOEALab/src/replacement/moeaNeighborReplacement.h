#pragma once

#include "../global.h"
#include "../subproblem/subproblem.h"
#include "../fitness/fitness.h"
/**
 * Neighbor replacement strategy that update niche neighbor .
 */
template < class MOEOT >
class moeaNeighborReplacement:public moeoReplacement < MOEOT >
{
public:
    moeaNeighborReplacement (moeaSubProblemFitnessAssignment < MOEOT > & _fitness,vector<moeaSubProblem> &_subProblems,moeaNormalized<MOEOT> &_normalized) :
            fitness (_fitness),subProblems(_subProblems),normalized(_normalized)
    {
        de = vector<unsigned int>(subProblems.size(),0);
    }

    virtual void operator()(eoPop<MOEOT> &A1, eoPop<MOEOT> &A2){}
    /**
     * Replaces the first population by adding the individuals of the second one, sorting with a moeoComparator and resizing the whole population obtained.
        * @param _parents the population composed of the parents (the population you want to replace)
        * @param _offspring the offspring population
     */
    virtual void operator () (MOEOT & _offspring,eoPop < MOEOT > &_pop,unsigned int _index)
    {
        //vector<double> && normOffspring = normalized(_offspring);
        vector<double> normOffspring = normalized(_offspring);
        vector<unsigned int>& neighborhood = subProblems[_index].neighbor;
        unsigned int nNiche = neighborhood.size();

        for (unsigned int i = 0; i < nNiche; ++i) {
            vector<double> & weight = subProblems[neighborhood[i]].weight;

            ///cout<<"neighbor["<<neighborhood[i]<<"] ("<<weight[0]<<","<<weight[1]<<")"<<endl;

            vector<double> normInd = normalized(_pop[neighborhood[i]]);
            double oFitness = fitness(normInd, subProblems[neighborhood[i]].weight);
            double nFitness = fitness(normOffspring, subProblems[neighborhood[i]].weight);

            //cout<<"old : "<<oFitness<<"  new : "<<nFitness<<endl;
            if (nFitness < oFitness) {

                // cout<<"before : "<<_pop[neighborhood[i]]<<endl;
                _pop[ neighborhood[i] ] = _offspring;
                c++;
                de[neighborhood[i]] = de[neighborhood[i]] +1;
                //cout<<"("<<c<<")old : "<<oFitness<<"  new : "<<nFitness<<"replace :"<<_pop[neighborhood[i]]<<endl;
            }
        }

        //for(unsigned int i =0;i<nNiche;i++)
         //   cout<<"["<<neighborhood[i]<<"] "<<_pop[neighborhood[i]]<<endl;

    }

    unsigned int c = 0;
    vector<unsigned int> de;
protected:

    /** the fitness assignment strategy */
    moeaSubProblemFitnessAssignment < MOEOT > & fitness;
    vector<moeaSubProblem> &subProblems;
    moeaNormalized<MOEOT> &normalized;

};


