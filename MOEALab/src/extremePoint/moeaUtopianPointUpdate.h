#pragma once

#include "../global.h"
#include "moeaExtremePoint.h"

template < class MOEOT>
class moeaUtopianPointUpdate : public moeaExtremePointUpdate<MOEOT>
{
public:

    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

    moeaUtopianPointUpdate(ObjectiveVector &_pUtopian):pUtopian(_pUtopian){}

    virtual bool operator()(const ObjectiveVector && _vec)
    {
        bool isUpdated = false;
        unsigned int nObj = ObjectiveVector::nObjectives();

        //cout<<nObj<<"["<<_vec[0]<<","<<_vec[1]<<"]("<<pUtopian[0]<<","<<pUtopian[1]<<")";
        for (unsigned int i = 0; i < nObj; ++i)
        {
            if(ObjectiveVector::minimizing(i)){
                //minimize
                if(pUtopian[i] > _vec[i])
                {
                    pUtopian[i] = _vec[i];
                    isUpdated = true;
                }
            }
            else
            {
                //maximize
                if(pUtopian[i] < _vec[i])
                {
                    pUtopian[i] = _vec[i];
                    isUpdated = true;
                }
            }
        }
        //if(isUpdated)
        //    cout<<"==>("<<pUtopian[0]<<","<<pUtopian[1]<<")";
       // cout<<endl;
        return isUpdated;
    }

    virtual void init(const ObjectiveVector &&_vec)
    {
        cout<<"Utopian INIT"<<endl;
        pUtopian = _vec;
        //copy(_vec.begin(),_vec.end(),pUtopian.begin());
    }

    virtual void printOut()
    {
        cout<<"Utopian :("<<pUtopian<<")"<<endl;
    }

private:
    ObjectiveVector & pUtopian;
};
