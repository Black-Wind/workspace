#pragma once

#include "../global.h"


class moeaSelectIndex
{
public:
    moeaSelectIndex(unsigned int _nPop):nPop(_nPop){}

    virtual unsigned int select()
    {
        return rng.uniform(nPop);
    }

    virtual unsigned int select(unsigned int _indexInd)
    {
        return this->select();
    }

    virtual void operator()(vector<unsigned int> &_selectList, unsigned int _num = 2)
    {
        unsigned int count = 0;
        unsigned int p;
        while(count < _num)
        {
            p = select();

            bool flag = true;
            for(unsigned int i=0; i<_selectList.size(); i++)
            {
                if(_selectList[i]==p) // p is in the list
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                _selectList.push_back(p);
                count++;
            }
        }
    }

    virtual void operator()(unsigned int _indexInd,vector<unsigned int> &_selectList, unsigned int _num = 2)
    {
        //cout<<"moeaSelectIndex"<<endl;
        unsigned int count = 0;
        unsigned int p;
        while(count < _num)
        {
            p = select(_indexInd);

            bool flag = true;
            for(unsigned int i=0; i<_selectList.size(); i++)
            {
                if(_selectList[i]==p) // p is in the list
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                _selectList.push_back(p);
                count++;
            }
        }
    }

    unsigned int nPop;
};

