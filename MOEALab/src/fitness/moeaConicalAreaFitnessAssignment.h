#pragma once

#include "../global.h"
#include "../extremePoint/extremePoint.h"

//Conical Area
template < class MOEOT >
class moeaCaFitnessAssignment
{
public:
    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename MOEOT::Fitness Fitness;

    moeaCaFitnessAssignment( ObjectiveVector &_pRef,unsigned int _nPop,eoEvalFunc<MOEOT> &_eval) :eval(_eval),pRef(_pRef),nPop(_nPop){}

    moeaCaFitnessAssignment( ObjectiveVector &_pRef,unsigned int _nPop) :eval(defaultEval),pRef(_pRef),nPop(_nPop){}

    //void operator()(MOEOT & _moeot){ }

    //void updateByDeleting(eoPop < MOEOT > & _pop, ObjectiveVector & _objVec){};

    //virtual void operator()(eoPop < MOEOT > & _pop){ }

    virtual Fitness operator() (MOEOT & _moeot,unsigned int _index, moeaNormalized<MOEOT> &_normalized)
    {
        if (_moeot.invalidObjectiveVector())
            eval(_moeot);
        Fitness res = this->operator()(_normalized(_moeot.objectiveVector()),_normalized(pRef),_index);
        _moeot.fitness(res);
        return res;
    }
/*
    virtual Fitness operator() (const vector<double> &&_vec,const vector<double>&& _pRef, unsigned int _index)
    {
        return this->operator()(_vec,_pRef,_index);
    }
*/
    virtual  string classname(){return "moeaConicalAreaFitnessAssignment";}

    /**
     * function which calculate the fitness from an objectiveVector (which has troi be valid.)
     * @param _mo an valid objectiveVector
     * @return the fitness value of _mo
     */
    virtual Fitness operator()(const vector<double> &  _vec, const vector<double> &_pRef, unsigned int _index){
        Fitness res = 1.0;

        if(_index == 0){
            res = 0.5*(_index+0.5)/(nPop - _index - 1.5)*_vec[1]*_vec[1] + (_pRef[1]- _vec[1])*_vec[0];
        }else if(_index == nPop - 1){
            res = 0.5*(nPop - _index -0.5 )/(_index - 0.5)*_vec[0]*_vec[0] + (_pRef[0]- _vec[0])*_vec[1];
        }else{
            res = 0.5*(nPop - _index - 0.5)/(_index - 0.5)*_vec[0]*_vec[0] + 0.5*(_index + 0.5)/(nPop - _index - 1.5) * _vec[1]*_vec[1] - _vec[0]*_vec[1];
        }
        return res;
    }

    virtual Fitness operator()(const vector<double> &  _vec, unsigned int _index , moeaNormalized<MOEOT> &_normalized){
        Fitness res;
        auto  ref = _normalized(pRef);
        res = this->operator()(_vec,ref,_index);
        ref.clear();
        return res;
    }

    ObjectiveVector &pRef;
    unsigned int nPop;

    class DummyEval: public eoEvalFunc<MOEOT>{
        void operator()(MOEOT &moeo){}
    }defaultEval;

    eoEvalFunc<MOEOT>& eval;
};
