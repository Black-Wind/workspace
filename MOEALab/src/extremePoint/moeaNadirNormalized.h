#pragma once

#include "../global.h"
#include "moeaNormalized.h"

template <class MOEOT>
class moeaNadirNormalized : public moeaNormalized<MOEOT>
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    moeaNadirNormalized(ObjectiveVector &_pUtopian,ObjectiveVector &_pNadir):moeaNormalized<MOEOT>(_pUtopian),pNadir(_pNadir){}

    virtual void operator()(const ObjectiveVector &_vec,vector<double> &norm)
    {
        unsigned int nObj = ObjectiveVector::nObjectives();
        norm.resize(nObj);
        double range;
        for(unsigned int i=0;i<nObj;i++)
        {
            range = fabs(pNadir[i] - this->pUtopian[i]);
            if(range < TOLERANCE)
                norm[i] = INF;
            else
                norm[i] = fabs((_vec[i] - this->pUtopian[i])/range);
        }
    }

    ObjectiveVector &pNadir;

};