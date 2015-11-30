#pragma once
#include "../global.h"
#include "./header.h"

class LCSTest
{
public:
	void simpleTest()
	{
		LCS ex;
		ex.getLCS("springtime","printing");
		ex.printV();
		ex.printLCS();

		ex.getLCS("ncaa tournament","north carolina");
		ex.printV();
		ex.printLCS();

		ex.getLCS("basketball","snoeyink");
		ex.printV();
		ex.printLCS();

	}
	void execute()
	{
		LCS ex;

		string s1,s2;
		stringstream sstr;
		ifstream input;
		clock_t start,finish;
		double duration=0.0;
		for (int i = 1; i <=10; ++i)
		{
			/* code */
			sstr.str("");
			sstr<<"./动态规划之字符串匹配测试数据/字符串"<<i<<".1.txt";
			input.open(sstr.str().c_str());
			input>>s1;
			input.close();

			sstr.str("");
			sstr<<"./动态规划之字符串匹配测试数据/字符串"<<i<<".2.txt";

			input.open(sstr.str().c_str());
			input>>s2;
			input.close();

			start=clock();
			ex.getLCS(s1, s2);
			cout<<"测试"<<i<<":"<<endl;
			ex.printLCS();
			finish=clock();
			duration+=(double)(finish-start)/CLOCKS_PER_SEC;;
			cout<<endl;	
		}

		cout << "一共耗时:"<<duration<<"s"<<endl;

	}
};