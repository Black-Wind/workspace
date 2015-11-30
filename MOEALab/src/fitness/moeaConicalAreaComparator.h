#pragma once

#include "../global.h"
#include "moeaConicalAreaFitnessAssignment.h"
#include "../extremePoint/extremePoint.h"
#include "../subproblem/subproblem.h"

template <class MOEOT>
class moeaConicalAreaComparator : public moeaConicalComparator<MOEOT>
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    moeaConicalAreaComparator(eoPop<MOEOT> &_pop,vector<moeaSubProblem> &_subProblems,moeaSubProblemMapping &_mapSubProblem,moeaNormalized<MOEOT> &_normalized,ObjectiveVector &_pRef,moeaCaFitnessAssignment<MOEOT> &_fitness):moeaConicalComparator<MOEOT>(_pop,_subProblems,_mapSubProblem,_normalized,_pRef),fitness(_fitness){}

    virtual bool operator()(const vector<double> &_vec1,const vector<double> &_vec2,unsigned int _index , Fitness &_finalFitness)
    {
        auto normRef = this->normalized(this->pRef);
        Fitness oFitness = fitness(_vec1,normRef,_index);
        Fitness nFitness = fitness(_vec2,normRef,_index);
        //conical area
        if(nFitness < oFitness)
        {
            _finalFitness = nFitness;
            return true;
        }
        _finalFitness = oFitness;
        return false;
    }

    virtual double diffFitness(unsigned int _ind)
    {
        double diff = 0;
        vector<double> normRef = this->normalized(this->pRef);
        MOEOT &ind = this->pop[this->mapSubProblem.pIndex(_ind)];
        vector<double> normInd = this->normalized(ind);
        unsigned int sIndex = this->locate(normInd);
        Fitness tFitness = fitness(normInd,normRef,sIndex);
        vector<unsigned int> & neighbor = this->subProblems[sIndex].neighbor;
        //cout<<"neighbor size : "<<neighbor.size()<<endl;
        for(unsigned int i=0;i<neighbor.size();i++)
        {
          //  cout<<neighbor[i]<<"  ["<<this->mapSubProblem.pIndex(neighbor[i])<<"]";
            MOEOT & neiInd = this->pop[this->mapSubProblem.pIndex(neighbor[i])];
            vector<double> normNei = this->normalized(neiInd);
            unsigned int neiIndex = this->locate(normNei);
            double neiFitness = fitness(normNei,normRef,neiIndex);
            //cout<<"diff fitness"<<(neiFitness - tFitness)<<endl;
            diff += (neiFitness - tFitness);
            normNei.clear();
        }
        diff /= neighbor.size();
        //cout<<"average diff :"<<diff<<endl;
        return diff;
    }
    moeaCaFitnessAssignment<MOEOT> &fitness;
};