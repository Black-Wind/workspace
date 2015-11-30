#pragma once

#include "../global.h"
#include "moeaHypervolumeFitnessAssignment.h"
#include "../extremePoint/extremePoint.h"
#include "../subproblem/subproblem.h"

template <class MOEOT>
class moeaConicalHyperVolumeComparator : public moeaConicalComparator<MOEOT>
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    moeaConicalHyperVolumeComparator(eoPop<MOEOT> &_pop,vector<moeaSubProblem> &_subProblems,moeaSubProblemMapping &_mapSubProblem,moeaNormalized<MOEOT> &_normalized,ObjectiveVector &_pRef,moeaHvFitnessAssignment<MOEOT> &_fitness,unsigned int _nH)
            :moeaConicalComparator<MOEOT>(_pop,_subProblems,_mapSubProblem,_normalized,_pRef),fitness(_fitness),nH(_nH){}

    virtual bool operator()(const vector<double> &_vec1,const vector<double> &_vec2,unsigned int _index , Fitness &_finalFitness)
    {
        unsigned int nObj = ObjectiveVector::nObjectives();
        vector<double> dRef(nObj);
        double k1 = std::accumulate(_vec1.begin(),_vec1.end(),0.0);
        double k2 = std::accumulate(_vec2.begin(),_vec2.end(),0.0);
        double k = max(k1,k2);
        for(unsigned int i=0;i<nObj;i++)
            dRef[i] = k * (1.0 +this->subProblems[_index].observe[i])/nH;

        Fitness oFitness = fitness(_vec1,dRef);
        Fitness nFitness = fitness(_vec2,dRef);
        //conical area
        if(nFitness > oFitness)
        {
            _finalFitness = nFitness;
            return true;
        }
        _finalFitness = oFitness;
        return false;
    }
    virtual double diffFitness(unsigned int _ind)
    {
        double diff = 0.0;
        vector<double>&& normRef = this->normalized(this->pRef);
        MOEOT &ind = this->pop[this->mapSubProblem.pIndex(_ind)];
        vector<double>&& normInd = this->normalized(ind);
        unsigned int sIndex = this->locate(normInd);
        Fitness tFitness = fitness(normInd,normRef);
        vector<unsigned int> & neighbor = this->subProblems[sIndex].neighbor;
        for(unsigned int i=0;i<neighbor.size();i++)
        {
            MOEOT & neiInd = this->pop[this->mapSubProblem.pIndex(neighbor[i])];
            vector<double>&& normNei = this->normalized(neiInd);
            unsigned int neiIndex = this->locate(normNei);
            double neiFitness = fitness(normNei,normRef);
            diff += (tFitness - neiFitness);
            normNei.clear();
        }
        diff /= neighbor.size();
        return diff;
    }
    moeaHvFitnessAssignment<MOEOT> &fitness;
    unsigned int nH;
};