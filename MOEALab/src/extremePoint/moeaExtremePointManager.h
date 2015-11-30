#pragma once

#include "../global.h"
#include "moeaExtremePoint.h"
#include "moeaReferencePointUpdate.h"
#include "moeaUtopianPointUpdate.h"
#include "moeaNadirPointUpdate.h"
#include "moeaAnchorPointUpdate.h"


template<class MOEOT>
class moeaExtremePointManager
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

    moeaExtremePointManager():pUtopianUpdate(emptyPoint),pNadirUpdate(emptyPoint),pRefUpdate(emptyPoint),pAnchorUpdate(emptyPoint){}

    moeaExtremePointManager(moeaUtopianPointUpdate<MOEOT> &_pUtopianUpdate):pUtopianUpdate(_pUtopianUpdate),pNadirUpdate(emptyPoint),pRefUpdate(emptyPoint),pAnchorUpdate(emptyPoint){}
    moeaExtremePointManager(moeaNadirPointUpdate<MOEOT> &_pNadirUpdate):pUtopianUpdate(emptyPoint),pNadirUpdate(_pNadirUpdate),pRefUpdate(emptyPoint),pAnchorUpdate(emptyPoint){}

    moeaExtremePointManager(moeaUtopianPointUpdate<MOEOT> &_pUtopianUpdate,moeaNadirPointUpdate<MOEOT> &_pNadirUpdate):pUtopianUpdate(_pUtopianUpdate),pNadirUpdate(_pNadirUpdate),pRefUpdate(emptyPoint),pAnchorUpdate(emptyPoint){}
    moeaExtremePointManager(moeaUtopianPointUpdate<MOEOT> &_pUtopianUpdate,moeaReferencePointUpdate<MOEOT> &_pRefUpdate):pUtopianUpdate(_pUtopianUpdate),pNadirUpdate(emptyPoint),pRefUpdate(_pRefUpdate),pAnchorUpdate(emptyPoint){}
    moeaExtremePointManager(moeaUtopianPointUpdate<MOEOT> &_pUtopianUpdate,moeaAnchorPointsUpdate<MOEOT> &_pAnchorUpdate):pUtopianUpdate(_pUtopianUpdate),pNadirUpdate(emptyPoint),pRefUpdate(emptyPoint),pAnchorUpdate(_pAnchorUpdate){}

    moeaExtremePointManager(moeaUtopianPointUpdate<MOEOT> &_pUtopianUpdate,moeaReferencePointUpdate<MOEOT> &_pRefUpdate,moeaAnchorPointsUpdate<MOEOT> &_pAnchorUpdate):pUtopianUpdate(_pUtopianUpdate),pNadirUpdate(emptyPoint),pRefUpdate(_pRefUpdate),pAnchorUpdate(_pAnchorUpdate){}

    moeaExtremePointManager(moeaUtopianPointUpdate<MOEOT> &_pUtopianUpdate,moeaNadirPointUpdate<MOEOT> &_pNadirUpdate,moeaReferencePointUpdate<MOEOT> &_pRefUpdate,moeaAnchorPointsUpdate<MOEOT> &_pAnchorUpdate):pUtopianUpdate(_pUtopianUpdate),pNadirUpdate(_pNadirUpdate),pRefUpdate(_pRefUpdate),pAnchorUpdate(_pAnchorUpdate){}

    virtual void init(const ObjectiveVector &&_vec)
    {
        cout<<"Extreme Point INIT"<<endl;
        pUtopianUpdate.init(std::forward<const ObjectiveVector>(_vec));
        pNadirUpdate.init(std::forward<const ObjectiveVector >(_vec));
        pRefUpdate.init(std::forward<const ObjectiveVector>(_vec));
        pAnchorUpdate.init(std::forward<const ObjectiveVector>(_vec));
        updateCount = 1;
    }

    virtual void init(const MOEOT &_indiv)
    {
        this->init( _indiv.objectiveVector());
    }
    virtual void init(const eoPop<MOEOT> &_pop)
    {
        unsigned int nPop = _pop.size();
        for(unsigned int i =0;i<nPop;i++)
            this->init(_pop[i].objectiveVector());
    }

    virtual bool update(const ObjectiveVector &&_vec)
    {
        bool isUpdated = false;
        // cout<<"Extreme Point UPDATE"<<endl;
        isUpdated |= pUtopianUpdate(std::forward<const ObjectiveVector>(_vec));
        isUpdated |= pNadirUpdate(std::forward<const ObjectiveVector >(_vec));
        pRefUpdate(std::forward<const ObjectiveVector>(_vec));
        pAnchorUpdate(std::forward<const ObjectiveVector>(_vec));
        if(isUpdated) updateCount++;
        return isUpdated;
    }

    virtual bool update(const MOEOT &_indiv)
    {
       // cout<<"update("<<_indiv.objectiveVector()<<")"<<endl;
        return this->update(_indiv.objectiveVector());
    }
    virtual bool update(const eoPop<MOEOT> &_pop)
    {
        unsigned int nPop = _pop.size();
        bool isUpdated = false;
        for(unsigned int i =0;i<nPop;i++)
            isUpdated |= this->update(_pop[i].objectiveVector());
        return isUpdated;
    }

    virtual void printOut()
    {
        pUtopianUpdate.printOut();
        pNadirUpdate.printOut();
        pRefUpdate.printOut();
        pAnchorUpdate.printOut();
    }

    unsigned int& updateVersion(){return updateCount;}

    class DummyExtremeUpdate : public moeaExtremePointUpdate<MOEOT>
    {
    public:
        typedef typename MOEOT::ObjectiveVector ObjectiveVector;

        bool operator()(const ObjectiveVector &&_vec){return false;}
        void init(const ObjectiveVector &&_vec){}
        void printOut(){cout<<"empty"<<endl;}
    } emptyPoint;

    moeaExtremePointUpdate < MOEOT > & pUtopianUpdate;
    moeaExtremePointUpdate < MOEOT > & pNadirUpdate;
    moeaExtremePointUpdate < MOEOT > & pRefUpdate;
    moeaExtremePointUpdate < MOEOT > & pAnchorUpdate;
    unsigned int updateCount;
};
