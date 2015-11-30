#pragma once

#include "../global.h"


class LCS
{
public:
	void getLCS(string _s1,string _s2)
	{
		Lcs.clear();
		s1.clear();
		s1.insert(s1.begin(), _s1.begin(),_s1.end());
		s2.clear();
		s2.insert(s2.begin(), _s2.begin(),_s2.end());

		std::vector<char> LCS;
		int row=s1.size(),col=s2.size();
		v.clear();
		isVisited.clear();
		v.resize(row+1);
		isVisited.resize(row+1);

		for(int i=0;i<=row;i++)
		{
			v[i].resize(col+1);
			isVisited[i].resize(col+1);
		}
		LCS_length(row,col);
		_getLCS(row,col);
	}
	void printV()
	{
		int row=v.size(),col=v[0].size();
		for (int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
				cout<< v[i][j]<<" ";
			cout <<endl;
		}
	}
	void printLCS()
	{
		int len=Lcs.size();
		cout<<"len: "<<len<<"   ";
		for (int i = 0; i < len; ++i)
		{
			/* code */
			cout<<Lcs[i];
		}
		cout<<endl;
	}
private:
	std::vector<char> Lcs;
	vector<vector <int> > v;
	vector<vector <bool> > isVisited;
	string s1,s2;
	int LCS_length(int m,int n)
	{
		if(m<0||n<0) return 0;
		if(isVisited[m][n])return v[m][n];

		if(m==0||n==0)
		{
			v[m][n]=0;
			isVisited[m][n]=true;
			return v[m][n];
		}
		if(s1[m-1]==s2[n-1])
			v[m][n]=LCS_length(m-1,n-1)+1;
		else
			v[m][n]=LCS_length(m, n-1)>LCS_length(m-1,n)?LCS_length(m,n-1):LCS_length(m-1, n);


		isVisited[m][n]=true;
		return v[m][n];
	}
	void _getLCS(int m,int n)
	{
		if(m==0||n==0)return;
		if(s1[m-1]==s2[n-1])
		{
			_getLCS(m-1,n-1);
			Lcs.push_back(s1[m-1]);
		}
		else
		{
			if(v[m][n-1]>v[m-1][n])
				_getLCS(m,n-1);
			else
				_getLCS(m-1,n);
		}
	}

};



