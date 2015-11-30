#pragma once

#include "../global.h"

template <class MOEOT>
class moeaNormalized
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

    moeaNormalized(ObjectiveVector &_pUtopian):pUtopian(_pUtopian){}

    virtual void operator()(const ObjectiveVector &_vec,vector<double> &norm)
    {
        unsigned int nObj = ObjectiveVector::nObjectives();
        norm.resize(nObj);
        for(unsigned int i =0;i<nObj;i++)
            norm[i] =fabs( _vec[i] - pUtopian[i]);
    }

    /*
    virtual void operator()(const ObjectiveVector &&_vec,vector<double> &norm)
    {
        this->operator()(_vec,norm);
    }
     */

    virtual vector<double> operator()(const ObjectiveVector &_vec)
    {
        vector<double> result;
        this->operator()(_vec,result);
        return result;
    }

    /*
    virtual vector<double> operator()(const ObjectiveVector &&_vec)
    {
        auto && result = this->operator()(_vec);
        return result;
    }*/

    virtual vector<double> operator()(const MOEOT& _moeot)
    {
        auto result = this->operator()(_moeot.objectiveVector());
        return result;
    }

    virtual void operator()(const MOEOT& _moeot,vector<double> &norm)
    {
        this->operator()(_moeot.objectiveVector(),norm);
    }

    ObjectiveVector &pUtopian;
};