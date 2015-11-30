#pragma once

#include "../global.h"
#include "moeaSubProblemFitnessAssignment.h"

//Tchebycheff approach
template < class MOEOT >
class moeaTCHFitnessAssignment : public moeaSubProblemFitnessAssignment<MOEOT>
{
public:
    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    //////////////////////////modified/////////////////////////////////////////////
    //using moeaSubProblemFitnessAssignment<MOEOT>::moeaSubProblemFitnessAssignment;
    moeaTCHFitnessAssignment<MOEOT>():moeaSubProblemFitnessAssignment<MOEOT>(){}
    moeaTCHFitnessAssignment<MOEOT>(eoEvalFunc<MOEOT> &_eval):moeaSubProblemFitnessAssignment<MOEOT>(_eval){}
    //using moeaSubProblemFitnessAssignment<MOEOT>::operator()(eoPop<MOEOT>&);

    /**
     * function which calculate the fitness from an objectiveVector (which has troi be valid.)
     * @param _mo an valid objectiveVector
     * @return the fitness value of _mo
     */
    virtual Fitness operator()(const vector<double> &_vec, const vector<double> & _weight) {
        unsigned int dim = _vec.size();
        Fitness res = -1.0e+30;
        double feval;
        //double diff;
        for (unsigned int l = 0; l < dim; l++) {
            //diff = _vec[l];

            if (_weight[l] < TOLERANCE) // equals to 0
            {
                feval = TOLERANCE * _vec[l];
            }
            else
                feval = _vec[l] * _weight[l];

            if (feval > res)
                res = feval;
        }

        // cout<<"TCH:"<<res<<endl;
        return res;
    }

    virtual  string classname(){return "moeaTCHFitnessAssignment";}

};

