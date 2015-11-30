#pragma once

#include "../global.h"
#include "moeaExtremePoint.h"


template <class MOEOT>
class moeaReferencePointUpdate : public moeaExtremePointUpdate<MOEOT>
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    moeaReferencePointUpdate(ObjectiveVector &_pRef,ObjectiveVector &_pUtopian):pRef(_pRef),pUtopian(_pUtopian){}

    virtual bool operator()(const ObjectiveVector && _vec)
    {
        bool isUpdated = false;
        unsigned int nObj = ObjectiveVector::nObjectives();

        for (unsigned int i = 0; i < nObj; ++i)
        {
            if(ObjectiveVector::minimizing(i)){
                //minimize
                if(pRef[i] < _vec[i])
                {
                    pRef[i]  = pUtopian[i] + 1e3 * (_vec[i] - pUtopian[i]);
                    isUpdated = true;
                }
            }
            else
            {
                //maximize
                if(pRef[i] > _vec[i])
                {
                    pRef[i] = pUtopian[i] - 1e3 * (pUtopian[i] - _vec[i] );
                    isUpdated = true;
                }
            }
        }
        return isUpdated;
    }
    virtual void init(const ObjectiveVector &&_vec)
    {
        cout<<"Reference INIT"<<endl;
        //copy(_vec.begin(),_vec.end(),pRef.begin());
        pRef = _vec;
    }
    virtual void printOut()
    {
        cout<<"Reference : ("<<pRef<<")"<<endl;
    }
private:
    ObjectiveVector &pRef;
    ObjectiveVector &pUtopian;
};
