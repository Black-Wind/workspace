#pragma once

#include "../global.h"
#include "../subproblem/subproblem.h"
#include "../extremePoint/extremePoint.h"

template < class MOEOT >
class moeaSubProblemFitnessAssignment
//:public eoEvalFunc < MOEOT >
{
public:
    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    moeaSubProblemFitnessAssignment(eoEvalFunc<MOEOT> &_eval) : eval(_eval){}

    moeaSubProblemFitnessAssignment() : eval(defaultEval){}

    //void operator()(MOEOT & _moeot){ }

    //void updateByDeleting(eoPop < MOEOT > & _pop, ObjectiveVector & _objVec){};

    /**
        * Sets the fitness values for every solution contained in the population _pop  (and in the archive)
        * @param _pop the population
        */
    //virtual void operator()(eoPop < MOEOT > & _pop){ }

    /**
   * Sets the fitness values for _moeot
   * @param _moeot the MOEOT
   */
    virtual Fitness operator() (MOEOT & _moeot,const vector<double>& _weight,moeaNormalized<MOEOT> &_normalized)
    {
        if (_moeot.invalidObjectiveVector())
            eval(_moeot);
        Fitness res = this->operator()(_normalized(_moeot.objectiveVector()),_weight);
        _moeot.fitness(res);
        return res;
    }

    virtual Fitness operator() (const vector<double> &_vec,const vector<double>& _weight)
    {
        Fitness res=0;

        unsigned int dim = _vec.size();
        for(unsigned int l=0; l<dim; l++){
            res += (_vec[l]) * _weight[l];
        }
        return res;
    }

    /*virtual Fitness operator() (const vector<double> &&_vec,const vector<double>& _weight)
    {
        return this->operator()(_vec,_weight);
    }
     */

    virtual  string classname(){return "moeaSubProblemFitnessAssignment";}


    class DummyEval: public eoEvalFunc<MOEOT>{
        void operator()(MOEOT &moeo){}
    }defaultEval;

    eoEvalFunc<MOEOT>& eval;
};
