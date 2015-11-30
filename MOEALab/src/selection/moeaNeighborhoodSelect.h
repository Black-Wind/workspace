#pragma once

#include "../global.h"
#include "../subproblem/subproblem.h"
#include "moeaSelectIndex.h"

template<class MOEOT>
class moeaNeighborhoodSelect : public eoSelectOne<MOEOT> ,public moeaSelectIndex
{
public:
	moeaNeighborhoodSelect(unsigned int _nPop,vector<moeaSubProblem> &_subProblems): moeaSelectIndex(_nPop),subProblems(_subProblems)
	{
		de = vector<unsigned int>(subProblems.size(),0);
	}

    const MOEOT & operator()(const eoPop<MOEOT> &_pop){return _pop[0];}

	virtual const MOEOT & operator() (const eoPop< MOEOT > &_pop,unsigned int _indexInd)
	{
		return _pop[ select(_indexInd) ];
	}

	virtual unsigned int select(unsigned int _indexInd)
	{
		return rng.choice(subProblems[_indexInd].neighbor);
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
				de[p]++;
				count++;
			}
		}
	}

	vector<moeaSubProblem> &subProblems;
	vector<unsigned int> de;
};
