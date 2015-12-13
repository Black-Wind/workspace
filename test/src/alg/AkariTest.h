#pragma once

#include "header.h"
#include "../global.h"



class AkariTest
{
public:
	void excute()
	{

	}
	void simpleTest()
	{
		double duration;
		ifstream input("data");

		while(input>>row>>col)
		{
			vector<vector<int> >map;
			map.resize(row);
			for (int i = 0; i < row; ++i)
			{
				map[i].resize(col);
				for (int j = 0; j < col; ++j)
				{
					input>>map[i][j];
				}
			}
			clock_t start=clock();
			Akari puzzle(map);
			puzzle.excute();
			clock_t finish=clock();
			duration=(double)(finish-start)/CLOCKS_PER_SEC;
			cout<<"花费了"<<duration<<"s"<<endl;
		}
		input.close();
	}
private:
	int row,col;
};