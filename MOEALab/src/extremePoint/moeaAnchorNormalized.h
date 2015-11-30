#pragma once

#include "../global.h"
#include "moeaNormalized.h"

template <class MOEOT>
class moeaAnchorNormalized : public moeaNormalized<MOEOT>
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    moeaAnchorNormalized(ObjectiveVector &_pUtopian,vector<ObjectiveVector> &_pAnchor ):moeaNormalized<MOEOT>(_pUtopian),pAnchor(_pAnchor){}

    virtual void operator()(const ObjectiveVector &_vec,vector<double> &norm)
    {
        unsigned int nObj = ObjectiveVector::nObjectives();
        norm.resize(nObj);
        double range;
        for(unsigned int i=0;i<nObj;i++)
        {
            range = fabs(pAnchor[i][i] - this->pUtopian[i]);
            if(range < TOLERANCE)
                norm[i] = INF;
            else
                norm[i] = fabs((_vec[i] - this->pUtopian[i])/range);
        }
    }

    vector<ObjectiveVector > &pAnchor;
};