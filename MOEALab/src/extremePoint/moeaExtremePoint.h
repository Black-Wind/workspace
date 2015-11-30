#pragma once

#include "../global.h"

template < class MOEOT>
class moeaExtremePointUpdate
{
public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

    virtual bool operator()(const ObjectiveVector && _vec) = 0;
    virtual bool operator()(const MOEOT & _indiv)
    {
        return this->operator()(_indiv.objectiveVector());
    };
    virtual void operator()(const eoPop < MOEOT > & _pop)
    {
        unsigned int nPop = _pop.size();
        for (unsigned int k=0; k < nPop; k++)
            this->operator()(_pop[k].objectiveVector());
    }

    virtual void init(const ObjectiveVector &&_vec) = 0;
    virtual void init(const MOEOT &_indiv)
    {
        this->init( _indiv.objectiveVector() );
    }
    virtual void init(const eoPop<MOEOT> &_pop)
    {
        unsigned int nPop = _pop.size();
        for(unsigned int k = 0;k<nPop;k++)
        {
            this->init(_pop[k].objectiveVector());
        }
    }

    virtual void printOut() = 0;
};
