#pragma once

#include "../global.h"


class greedyAlg
{
public:
	int _problem1(vector<int>&times)
	{
		sort(times.begin(),times.end());
		int totTime=0;
		int NUM=times.size();
		int L_NUM=NUM;
		while(L_NUM>3)
		{
			int i=L_NUM-1;
			if(times[0]+times[i-1]>2*times[1])
				totTime+=2*times[1]+times[0]+times[i];
			else
				totTime+=2*times[0]+times[i-1]+times[i];
			L_NUM-=2;
		}
		if(L_NUM==2)
			totTime+=times[1];
		else if(L_NUM==3)
			totTime+=times[0]+times[1]+times[2];
		return totTime;
	}

	int _problem2(vector<int>&times,int k)
	{
		sort(times.begin(),times.end());
		int totTime=0;

		std::vector<int> kT(times.size(),k);

		int NUM=times.size();
		int firstIndex=0,lastIndex=NUM-1;

		while(lastIndex-firstIndex>2)
		{
			//消除k=1的元素
			while(kT[firstIndex]==1)
			{
				int nextIndex=firstIndex+1;
				for(;nextIndex<lastIndex;nextIndex++)
					if(kT[nextIndex]>1)break;

			  if(nextIndex<lastIndex)
			  {
				totTime+=2*times[nextIndex];
				kT[firstIndex]--;
				kT[nextIndex]-=2;
				firstIndex++;

			  }
			  else if(nextIndex==lastIndex)
			  {
			  	totTime+=times[nextIndex];
			  	kT[firstIndex]--;
			  	kT[nextIndex]--;
			  	// firstIndex++;
			  }
			  else
			  {
			  	cout<<"debug error"<<endl;
			  }
			}
			if (lastIndex-firstIndex<=2)break;
			if(times[firstIndex]+times[lastIndex-1]>2*times[firstIndex+1])
			{
				totTime+=2*times[firstIndex+1]+times[firstIndex]+times[lastIndex];
				kT[firstIndex]-=2;
				kT[firstIndex+1]-=2;
				kT[lastIndex]--;

				lastIndex-=2;
			}
			else if(kT[firstIndex]!=3)
			{
				totTime+=2*times[firstIndex]+times[lastIndex-1]+times[lastIndex];
				kT[firstIndex]-=4;
				kT[lastIndex-1]--;
				kT[lastIndex]--;

				lastIndex-=2;
			}
			else
			{
				totTime+=times[lastIndex]+times[firstIndex];
				kT[firstIndex]-=2;
				kT[lastIndex]--;

				lastIndex--;
			}

		}

		if(lastIndex==firstIndex+1)
			totTime+=times[lastIndex];
		else if(lastIndex==firstIndex+2)
		{
			totTime+=times[firstIndex]+times[firstIndex+1]+times[lastIndex];
		}
		else
		{
			cout<<"note!:"<<lastIndex-firstIndex<<endl;
		}

		return totTime;
	}
};