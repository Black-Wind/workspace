#pragma once

#include "../global.h"


template <class MOEOT>
class moeaDiffXover
{
public:
    moeaDiffXover():rate(0.5),bounds(eoDummyVectorNoBounds){}

    moeaDiffXover(double _rate):rate(_rate),bounds(eoDummyVectorNoBounds){}

    moeaDiffXover(eoRealVectorBounds & _bounds):rate(0.5),bounds(_bounds){}

    moeaDiffXover(eoRealVectorBounds & _bounds , double _rate):rate(_rate),bounds(_bounds){}

    void operator()(MOEOT &_eo0, const MOEOT &_eo1, const MOEOT &_eo2, const MOEOT &_eo3)
    {
        unsigned int nVar = _eo1.size();
        unsigned int idx_rnd = int(rng.uniform(nVar));

        for(unsigned int n=0;n<nVar;n++){
            double rnd = rng.uniform(101)/100;
            if(rnd<1||n == idx_rnd)
                _eo0[n] = _eo1[n] + rate*(_eo2[n] - _eo3[n]);
            //else
                //_eo0[n] = _eo0[n];

            bounds.foldsInBounds(n, _eo0[n]);
        }
    }

    void operator()(MOEOT &_eo0, const MOEOT &_eo1, const MOEOT &_eo2)
    {
        unsigned int nVar = _eo1.size();
        for(unsigned int n=0;n<nVar;n++)
        {
            _eo0[n] = _eo0[n] + rate*(_eo2[n] - _eo1[n]);

           bounds.foldsInBounds(n, _eo0[n]);
        }
    }

    virtual string classname(){return "moeaDiffXover";}
    double rate;
    eoRealVectorBounds & bounds;
};

