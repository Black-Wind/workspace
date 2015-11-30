#pragma once

#include "../global.h"
#include "moeaExtremePoint.h"

template < class MOEOT>
class moeaNadirPointUpdate : public moeaExtremePointUpdate<MOEOT>
{
public:

    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

    moeaNadirPointUpdate(ObjectiveVector &_pNadir):pNadir(_pNadir){}

    virtual bool operator()(const ObjectiveVector && _vec)
    {
        bool isUpdated = false;
        unsigned int nObj = ObjectiveVector::nObjectives();

        for (unsigned int i = 0; i < nObj; ++i)
        {
            if(ObjectiveVector::minimizing(i)){
                //minimize
                if(pNadir[i] < _vec[i])
                {
                    pNadir[i] = _vec[i];
                    isUpdated = true;
                }
            }
            else
            {
                //maximize
                if(pNadir[i] > _vec[i])
                {
                    pNadir[i] = _vec[i];
                    isUpdated = true;
                }
            }
        }

        return isUpdated;
    }

    virtual void init(const ObjectiveVector &&_vec)
    {
        cout<<"pNadir INIT"<<endl;
        //copy(_vec.begin(),_vec.end(),pNadir.begin());
        pNadir = _vec;
    }

    virtual void printOut()
    {
        cout<<"pNadir :("<<pNadir<<")"<<endl;
    }

    virtual string classname(){return "moeaNadirPointUpdate";}
private:
    ObjectiveVector & pNadir;
};
