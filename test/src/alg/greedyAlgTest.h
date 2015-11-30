#pragma once

#include "../global.h"
#include "./header.h"
class greedyAlgTest
{
public:
	void test()
	{
		greedyAlg alg;
		vector<int>times;
		times.push_back(1);
		times.push_back(6);
		times.push_back(8);
		times.push_back(9);
		times.push_back(10);
		cout<<"过桥时间:"<<alg._problem2(times,3)<<endl;
	}
	void problem1()
	{
		cout<<"问题1:"<<endl;
		greedyAlg alg;
		ifstream input("贪心法测试数据.txt");
		std::vector<int> times;
		string tmp;


		for(int i=0;i<3;i++)
			input>>tmp;

		times.clear();
		times.resize(200);
		for(int i=0;i<200;i++)
			input>>times[i];
		cout<<"测试数据1过桥时间:"<<alg._problem1(times)<<endl;

		times.clear();
		times.resize(500);
		for(int i=0;i<3;i++)
			input>>tmp;
		for(int i=0;i<500;i++)
			input>>times[i];
		cout<<"测试数据2过桥时间:"<<alg._problem1(times)<<endl;
		input.close();
	}
	void problem2()
	{
		cout<<"问题2:"<<endl;
		greedyAlg alg;
		ifstream input("贪心法测试数据.txt");
		std::vector<int> times;
		string tmp;


		for(int i=0;i<3;i++)
			input>>tmp;

		times.clear();
		times.resize(200);
		for(int i=0;i<200;i++)
			input>>times[i];
		cout<<"测试数据1"<<endl;
		for(int i=3;i<66;i+=2)
			cout<<"k="<<i<<" 过桥时间:"<<alg._problem2(times,i)<<endl;

		times.clear();
		times.resize(500);
		for(int i=0;i<3;i++)
			input>>tmp;
		for(int i=0;i<500;i++)
			input>>times[i];
		cout<<"测试数据2"<<endl;
		for(int i=3;i<66;i+=2)
			cout<<"k="<<i<<" 过桥时间:"<<alg._problem2(times,i)<<endl;
		input.close();
	}

};