#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <ctime>
#include <stack>
using namespace std;

#define ROOT 1

class ArticulationPointRevealer
{
public:
	ArticulationPointRevealer()
	{
		NUM_POINT=0;
		d=0;
		inputFileName="input";
	}
	ArticulationPointRevealer(int num,string name)
	{
		NUM_POINT=num;
		d=0;
		inputFileName=name;
	}
	void test();//测试函数
	int  NUM_POINT;
	string inputFileName;
private:
	/*
		辅助函数
	 */
	void Init();
	void scanInput();
	void print();

	int  dfs(int pointIndex);
	void ndfs(int node);

	std::vector<vector<bool> > Matrix;//邻接矩阵

	std::vector<bool> isVisited;//记录各节点是否被访问过
	std::vector<int> dVector;//记录各节点被访问的序号
	std::set <int> ArticulationPoint;//保存关节点
	std::vector<vector<int> >adjacencyLists;
	int  d;
	std::stack<int>stack;			 //栈
	std::vector<int>low;
};
