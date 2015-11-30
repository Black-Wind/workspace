#pragma once

#include "../global.h"
#include "../extremePoint/extremePoint.h"
#include "moeaSubProblemMapping.h"
#include "moeaSubProblemLocate.h"
#include "../fitness/fitness.h"


template <class MOEOT>
class moeaSubProblemMappingUpdate
{
public:
    typedef typename MOEOT::Fitness Fitness;

    moeaSubProblemMappingUpdate(vector<moeaSubProblem> &_subProblem,moeaSubProblemMapping &_mapSubProblem,moeaNormalized<MOEOT> &_normalized,moeaConicalComparator<MOEOT> &_comparator):subProblem(_subProblem),mapSubProblem(_mapSubProblem),normalized(_normalized),comparator(_comparator){}

    void operator()(eoPop <MOEOT> &_pop) {
        unsigned int nPop = _pop.size();

        vector<bool> flag(nPop, false);

        vector<vector<double> > normPop(nPop);

        //cout<<"map updating 1"<<endl;
        for (unsigned int n = 0; n < nPop; n++) {
            normalized(_pop[n], normPop[n]);

            if (!mapSubProblem.check(n)) {
                unsigned int actualS = locate(normPop[n]);
                mapSubProblem.setActualIndex(n, actualS);
            }
        }

        vector<unsigned int> restPopIndex;
        for (unsigned int n = 0; n < nPop; n++) {
            unsigned int actualS = mapSubProblem.actualIndex(n);
            if (!flag[actualS]) {
                // cout<<"map updating new"<<endl;
                mapSubProblem.bind(actualS, n);
                flag[actualS] = true;
            }
            else {
                //cout<<"map updating old"<<endl;
                Fitness fitness;
                unsigned int oldPIndex = mapSubProblem.pIndex(actualS);
                if (comparator(normPop[oldPIndex], normPop[n], actualS, fitness)) {
                    //cout<<"replace"<<endl;
                    mapSubProblem.bind(actualS, n);
                }
                else
                    oldPIndex = n;
                //cout<<"restore index : "<<oldPIndex<<endl;
                restPopIndex.push_back(oldPIndex);
            }
        }

        //cout<<"end fenpei"<<endl;
        normPop.clear();

        eoQuadDistance<vector<unsigned int> > distance;

        unsigned int restSize = restPopIndex.size();
        for (unsigned int i = 0; i < nPop; i++) {
            //cout<<restSize<<" ["<<i<<"]  "<<flag[i]<<endl;
            if (!flag[i]) {
                unsigned int minIndex = restPopIndex[restSize - 1];
                double minDis = distance(subProblem[i].observe, subProblem[mapSubProblem.actualIndex(minIndex)].observe);
                //cout<<"["<<minIndex<<"]"<<minDis<<endl;
                for (int j = restSize - 2; j >= 0; j--) {
                    // cout<<j<<endl;
                    unsigned int index = restPopIndex[j];
                    double tmpDis = distance(subProblem[i].observe, subProblem[mapSubProblem.actualIndex(index)].observe);
                    //cout<<"["<<restPopIndex[j]<<"]"<<tmpDis<<endl;
                    if (tmpDis < minDis) {
                        restPopIndex[restSize - 1] = restPopIndex[j];
                        restPopIndex[j] = minIndex;
                        minIndex = restPopIndex[restSize - 1];
                        minDis = tmpDis;
                    }
                }
                mapSubProblem.bind(i, minIndex);
                flag[i] = true;
                restSize--;
            }
        }

        //cout<<"map updating end"<<endl;
        flag.clear();
    }

    moeaSubProblemMapping &mapSubProblem;
    moeaNormalized<MOEOT> &normalized;
    moeaSubProblemLocate locate;
    vector<moeaSubProblem> &subProblem;
    moeaConicalComparator<MOEOT> &comparator;
};