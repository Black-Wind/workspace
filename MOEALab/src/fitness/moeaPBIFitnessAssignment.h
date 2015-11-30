#pragma once

#include "../global.h"

#include "moeaSubProblemFitnessAssignment.h"


//Boundary intersection approach
template < class MOEOT >
class moeaPBIFitnessAssignment : public moeaSubProblemFitnessAssignment<MOEOT>
{
public:
    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    moeaPBIFitnessAssignment() :moeaSubProblemFitnessAssignment<MOEOT>(),theta(5){}

    moeaPBIFitnessAssignment(double _theta) :moeaSubProblemFitnessAssignment<MOEOT>(),theta(_theta){}

    moeaPBIFitnessAssignment(eoEvalFunc<MOEOT> &_eval) :moeaSubProblemFitnessAssignment<MOEOT>(_eval),theta(5){}

    moeaPBIFitnessAssignment(eoEvalFunc<MOEOT> &_eval,double _theta) :moeaSubProblemFitnessAssignment<MOEOT>(_eval),theta(_theta){}

    /**
     * function which calculate the fitness from an objectiveVector (which has troi be valid.)
     * @param _mo an valid objectiveVector
     * @return the fitness value of _mo
     */
    virtual Fitness operator()(const vector<double> &_vec ,const vector<double> & _weight){

        unsigned int dim = _vec.size();
        Fitness res = -1.0e+30;
        // normalize the weight vector (line segment)
        //double nd = sqrt((double)inner_product(_weight.begin(),_weight.end(),_weight.begin(),0.0) );

        //realA equal to _vec
        vector <double> realB(dim);

        // distance along the line segment
        double d1 = fabs(inner_product(_vec.begin(),_vec.end(),_weight.begin(),0.0)) ;/// nd;

        // distance to the line segment
        for(unsigned int l=0; l < dim; l++) {
            realB[l] = _vec[l] - d1*_weight[l];///nd;
        }

        double d2 = sqrt(inner_product(realB.begin(),realB.end(),realB.begin(),0.0));

        res = d1 + theta *d2;

        realB.clear();
        return res;

    }

    virtual string classname(){return "moeaPBIFitnessAssignment";}

    double theta;

};
