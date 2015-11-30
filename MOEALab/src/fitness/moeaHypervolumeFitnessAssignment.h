#pragma once

#include "../global.h"

//Local hypervolume
template < class MOEOT >
class moeaHvFitnessAssignment
{
public:
    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;
    moeaHvFitnessAssignment(eoEvalFunc<MOEOT> &_eval) :eval(_eval){}

    moeaHvFitnessAssignment() :eval(defaultEval){}

   // void operator()(MOEOT & _moeot){ }

   // void updateByDeleting(eoPop < MOEOT > & _pop, ObjectiveVector & _objVec){};

   // virtual void operator()(eoPop < MOEOT > & _pop){ }

    virtual Fitness operator() (MOEOT & _moeot,const ObjectiveVector & _pRef, moeaNormalized<MOEOT> &_normalized)
    {
        if (_moeot.invalidObjectiveVector())
            eval(_moeot);
        Fitness res = this->operator()(_normalized(_moeot.objectiveVector()),_normalized(_pRef));
        _moeot.fitness(res);
        return res;
    }

    virtual Fitness operator() (const vector<double> &&_vec,const vector<double>&& _pRef)
    {
        return this->operator()(_vec,_pRef);
    }

    /**
     * function which calculate the fitness from an objectiveVector (which has troi be valid.)
     * @param _mo an valid objectiveVector
     * @return the fitness value of _mo
     */
    virtual Fitness operator()(const vector<double> &  _vec, const vector<double> &_pRef){
        unsigned int dim = _vec.size();
        Fitness res = 1.0;

        for (unsigned int l = 0; l < dim; l++)
        {
            res *= fabs(_pRef[l] - _vec[l]);
        }
        return res;
    }

    virtual  string classname(){return "moeaHvFitnessAssignment";}

    class DummyEval: public eoEvalFunc<MOEOT>{
        void operator()(MOEOT &moeo){}
    }defaultEval;

    eoEvalFunc<MOEOT>& eval;
};
