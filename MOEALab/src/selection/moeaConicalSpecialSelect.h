#pragma once

#include "../global.h"
#include "moeaSelectIndex.h"

class moeaConicalSpecialSelect : public moeaSelectIndex
{
public:
    moeaConicalSpecialSelect(moeaSelectIndex &_selection,unsigned int _nPop,unsigned int _nObj, unsigned int _nH,unsigned int _sCount, unsigned int _type=1):selection(_selection),sCount(_sCount),moeaSelectIndex(_nPop)
    {
        vector<unsigned int> tmp(_nObj, 0);
        if(_type == 1) {
            for (unsigned int i = 0; i < _nObj; i++) {
                tmp[i] = _nH;
                sList.push_back(locate.locateIndex(tmp));
                tmp[i] = 0;
            }
        }
        else if(_type == 2)
        {
            for(unsigned int i = 0;i<_nObj;i++)
            {
                for(unsigned int j=i+1;j<_nObj;j++)
                {
                    for(unsigned int p =0;p <= _nH;p++)
                    {
                        tmp[i] = p;
                        tmp[j] = _nH - p;
                        sList.push_back(locate.locateIndex(tmp));
                        tmp[i] = 0;
                        tmp[j] = 0;
                    }
                }
            }
        }

        de = vector<unsigned int>(_nPop,0);
    }

    virtual void operator()(vector<unsigned int> &_selectList, unsigned int _num = 2)
    {
        c++;
        if (c % sCount == 0) {
           // cout<<"special :"<<c<<endl;
            _selectList.push_back(rng.choice(sList));

            c = 0;

            selection(_selectList,_num-1);
        }
        else
            selection(_selectList,_num);

        for(unsigned int i=0;i<_num;i++)
            de[_selectList[i]]++;
    }

    virtual void operator()(unsigned int _indexInd,vector<unsigned int> &_selectList, unsigned int _num = 2)
    {
        this->operator()(_selectList,_num);
    }

    moeaSelectIndex &selection;
    moeaSubProblemLocate locate;
    unsigned int sCount;
    unsigned int c = 0;
    vector<unsigned int> sList;
    vector<unsigned int> de;
};
