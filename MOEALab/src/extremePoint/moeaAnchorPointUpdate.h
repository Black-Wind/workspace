#pragma once

#include "../global.h"
#include "moeaExtremePoint.h"

template <class MOEOT>
class moeaAnchorPointsUpdate :public moeaExtremePointUpdate<MOEOT>
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    moeaAnchorPointsUpdate(ObjectiveVector &_pUtopian, vector<ObjectiveVector> &_pAnchor):pUtopian(_pUtopian),pAnchor(_pAnchor){}

    virtual bool operator()(const ObjectiveVector && _vec)
    {
        bool isUpdated = false;
        unsigned int nObj = ObjectiveVector::nObjectives();
        /*
        for (int i = 0; i < nObj; ++i) {
            if((ObjectiveVector::minimizing(1-i) && _vec[1-i] < pAnchor[i][1-i]) \
                || (ObjectiveVector::maximizing(1-i) && _vec[1-i] > pAnchor[i][1-i]) \
                ||((fabs(_vec[1 -i] - pAnchor[i][1 - i]) < TOLERANCE ) && _vec.dominates(pAnchor[i])))
            {
                copy(_vec.begin(),_vec.end(),pAnchor[i].begin());
                isUpdated = true;
            }
        }
        */
        for(unsigned int i=0;i<nObj;i++)
        {
            if(_vec.dominates(pAnchor[i]))
            {
                copy(_vec.begin(),_vec.end(),pAnchor[i].begin());
                isUpdated = true;
            }
            else
            {
                for(unsigned int j=0;j<nObj;j++)
                {
                    if(j == i) continue;
                    if((ObjectiveVector::minimizing(j)&&(_vec[j] < pAnchor[i][j]))\
                     ||(ObjectiveVector::maximizing(j)&&(_vec[j] > pAnchor[i][j])))
                    {
                        pAnchor[i][j] = _vec[j];
                        isUpdated = true;
                    }
                }
            }
        }
        return isUpdated;
    };

    virtual void init(const ObjectiveVector &&_vec)
    {
        unsigned int nObj = ObjectiveVector::nObjectives();
        for(unsigned int i=0;i<nObj;i++)
        {
            pAnchor.push_back(_vec);
        }
    }

    virtual void printOut()
    {
        cout<<"Anchor point";
        unsigned int nObj = ObjectiveVector::nObjectives();
        for(unsigned int i=0;i<nObj;i++)
        {
            cout<<"["<<i<<"]("<<pAnchor[i]<<")";
        }
    }
private:
    vector<ObjectiveVector> &pAnchor;
    ObjectiveVector &pUtopian;
};
