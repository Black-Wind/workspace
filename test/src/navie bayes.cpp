//
#include "navie bayes.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void naiveBayes(){

	ifstream in;
	in.open("public.txt");
	char line[100];
	in.getline(line,100);
	in.getline(line,100);

	long int times=0,Gtimes=0,nineTimes=0,nine2Times=0,nine1Times=0;

	vector<int> v1,v2,v3,v4,v5,v6;
	v1.resize(10);
	v2.resize(10);
	v3.resize(10);
	v4.resize(10);
	v5.resize(10);
	v6.resize(10);

	double pri=0.0;
	while(!in.eof())
	{
		int fchatnum,cchatnum,remark;
		in>>fchatnum>>cchatnum>>remark;
		times++;
		v1[fchatnum-1]++;
		v6[cchatnum-1]++;
		if(fchatnum==9&&cchatnum==9)
			nineTimes++;



		if(remark==2){
			Gtimes++;
			v2[fchatnum-1]++;
			v3[cchatnum-1]++;
			if(fchatnum==9&&cchatnum==9)
				nine2Times++;
		}

		if(remark==1){
			v4[fchatnum-1]++;
			v5[cchatnum-1]++;
			if(fchatnum==9&&cchatnum==9)
				nine1Times++;
		}





	}
	pri=(double)Gtimes/times;
	printf("%.3f\n",pri);
	for(int i=0;i<9;i++)
		printf("%.3f,",(v2[i])/(pri*times));
	printf("%.3f\n",(v2[9])/(pri*times));

	double k=((1-pri)*v4[8]/((1-pri)*times)*v5[8]/((1-pri)*times) )/(pri*v2[8]/(pri*times)*v3[8]/(pri*times));
	printf("%.3f\n",1/(1+k));

	double tmp1,tmp2,tmp3,tmp4;
	cout<<(tmp1=(double)v2[8]*v3[8]/times/times/pri/pri)<<" "<<(tmp2=(double)nine2Times/times/pri)<<endl;

	cout<<(tmp3=(double)v4[8]*v5[8]/times/times/(1-pri)/(1-pri))<<" "<<(tmp4=(double)nine1Times/times/(1-pri))<<endl;

	k=tmp3*(1-pri)/tmp1/pri;
	printf("%.3f\n",1/(1+k));

	k=tmp4*(1-pri)/tmp2/pri;
	printf("%.3f\n",1/(1+k));

	cout<<(double)nineTimes/times<<" "<<(double)v1[8]*v6[8]/times/times<<" "<<v1[8]<<" "<<v6[8]<<endl ;
}









