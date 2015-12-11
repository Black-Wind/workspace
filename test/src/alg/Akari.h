#pragma once
#include "../global.h"

#define BLACK0 		0
#define BLACK1 		1
#define BLACK2 		2
#define BLACK3 		3
#define BLACK4 		4
#define BLACK  		5
#define WHITE  		9
#define LIGHT   	6
#define ILLUMINATED 7
#define FORBIDDENED 8

class Akari
{
public:
	Akari(vector<vector<int> > _map)
	{
		realRow=_map.size();
		row=realRow+2;
		realCol=_map[0].size();
		col=realCol+2;
		map.resize(row);

		newLine(map[0]);
		newLine(map[row-1]);

		for (int i = 0; i < realRow; ++i)
		{
			/* code */
			newLine(map[i+1]);

			for(int j=0;j<realCol;j++)
				map[i+1][j+1]=_map[i+1][j+1];
		}
		/**
		 * debug
		 */
		 print();
	}
	void excute()
	{
		/**
		 * pre-
		 */
		pattern_match_loop(map);
		Local_search();
		print();
	}
private:
	int col,row;
	int realCol,realRow;
	vector<vector<int> > map;
	stack<vector<vector<int> > >map_stack;

	void pattern_match_loop(vector <vector<int> >&_map)
	{
		bool flag=true;
		while(flag)
		{
			flag=pattern_match(_map);
		}
	}
	bool pattern_match(vector<vector<int> >&_map)
	{

	}
	void Local_search()
	{
		while(isDone())
		{

		}
	}
	void _Local_search()
	{

	}
	bool check()
	{

	}
	bool isDone()
	{
		bool flag=true;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				/* code */
				if(map[i][j]==WHITE||map[i][j]==FORBIDDENED)
					flag=false;
			}
		}
		flag=flag&&check();
		return flag;
	}
	void newLine(vector<int>&line)
	{
		line.resize(col);
		for (int i = 0; i < line.size(); ++i)
		{
			/* code */
			line[i]=BLACK;
		}
	}

	void print()
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				/* code */
				cout<<map[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	void copy(vector<<vector<int> >&_map)
	{
		_map.resize(row);
		for (int i = 0; i < row; ++i)
		{
			_map[i].resize(col);
			for (int j = 0; j < col; ++j)
			{
				/* code */
				_map[i][j]=map[i][j];
			}
		}
	}
	void wirte(vector<vector<int> >&_map)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				/* code */
				map[i][j]=_map[i][j];
			}
		}
	}
};
