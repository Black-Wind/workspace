#pragma once

#include "../global.h"
#include "moeaSubProblem.h"
#include "moeaSubProblemLocate.h"

class moeaSubProblemMapping {
public:
    moeaSubProblemMapping(unsigned int _nPop, unsigned int &_updateVersion) : nPop(_nPop),updateVersion(_updateVersion)
    {
        init();
    }
    ~moeaSubProblemMapping() {
        PinS.clear();
        StoP.clear();
        actualS.clear();
        version.clear();
    }

    void init() {
        PinS.resize(nPop);
        StoP.resize(nPop);
        actualS.resize(nPop);
        version.resize(nPop);
        for (unsigned int i = 0; i < nPop; i++) {
            PinS[i] = 101;//i;
            StoP[i] = 101;//i;
            actualS[i] = 101;//i;
            version[i] = 0;
        }
    }

    unsigned int bind(unsigned int _sIndex, unsigned int _pIndex) {
        unsigned int oIndex = PinS[_sIndex];
        PinS[_sIndex] = _pIndex;
        StoP[_pIndex] = _sIndex;
        return oIndex;
    }

    bool check(unsigned int _index)
    {
        return version[_index] == updateVersion;
    }

    unsigned int pIndex(unsigned int _sIndex)
    {
        return PinS[_sIndex];
    }

    unsigned int sIndex(unsigned int _pIndex)
    {
        return StoP[_pIndex];
    }

    unsigned int actualIndex(unsigned int _pindex)
    {
        return actualS[_pindex];
    }

    unsigned int setActualIndex(unsigned int _popIndex, unsigned int _sIndex)
    {
        actualS[_popIndex] = _sIndex;
        version[_popIndex] = updateVersion;
    }

    unsigned int getVersion(unsigned int _index)
    {
        return version[_index];
    }

    vector<unsigned int> PinS;
    vector<unsigned int> StoP;
    vector<unsigned int> actualS;
    vector<unsigned int> version;

    unsigned int nPop;
    unsigned int &updateVersion;
};