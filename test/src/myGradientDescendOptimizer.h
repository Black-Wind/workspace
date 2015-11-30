#ifndef _GRADIENTDESCENDOPTMIZER_
#define _GRADIENTDESCENDOPTMIZER_

#include <cmath>
#include <stdlib.h>
#include <iostream>

using namespace std;

template <class T>
class myGradientDescendOptimizer{

public:
	myGradientDescendOptimizer(T _varible,int _numVarible,double (*_f)(T ,int),double _alpha,int _max_step);
	~myGradientDescendOptimizer();
	void optimize();
	void setDelta(double);
private:
	T varible;
	int numVarible;
	double (*f)(T ,int);
	double *derivative;
	double alpha;
	int max_step;
	double delta;

};

template <class T>
myGradientDescendOptimizer<T>::myGradientDescendOptimizer(
		T _varible,int _numVarible,double (*_f)(T ,int),double _alpha,int _max_step):
		varible(_varible),numVarible(_numVarible),f(_f),alpha(_alpha),max_step(_max_step)
		{
			derivative=(double*)malloc(sizeof(double)*numVarible);
			delta=1e-6;
		}

template <class T>
myGradientDescendOptimizer<T>::~myGradientDescendOptimizer(){

	free(derivative);
}
template <class T>
void myGradientDescendOptimizer<T>::setDelta(double _delta){
	delta=_delta;
}

template <class T>
void myGradientDescendOptimizer<T>::optimize(){

	double lastF=0.0,curF=0.0,deriSum=0.0;
	for(int i=0;i<max_step;i++)
	{
		deriSum=0.0;
		for(int j=0;j<numVarible;j++)
		{
			varible[j]+=delta;//////////////////////!!!!!!!/////////////////根据T修改
			derivative[j]=(*f)(varible,numVarible);
			varible[j]-=delta;//////////////////////!!!!!!!/////////////////根据T修改
			derivative[j]-=(*f)(varible,numVarible);
			derivative[j]/=delta;

			deriSum+=derivative[j]*derivative[j];
		}
		//////////////////////归一化//////////////////////////////////////////////////
		deriSum=sqrt(deriSum);

		for(int j=0;j<numVarible;j++){
			derivative[j]/=deriSum;
			varible[j]-=alpha*derivative[j];//////////////////////!!!!!!!/////////////////根据T修改
		}

		curF=(*f)(varible,numVarible);
		if(curF<lastF)alpha*=1.2;   ///////最小化///////////
		else alpha*=0.5;
		lastF=curF;
	}

}

inline double fun(double *varible,int numVarible){
	double f=0.0;
	for(int i=0;i<numVarible;i++)
		f+=(varible[i]-1)*(varible[i]-1);
	return f;
}

inline void myGadientDescendOptimizerTest(){
		int numVarible=2;
		double *varible=(double*)malloc(sizeof(double)*numVarible);
		varible[0]=2.0;
		varible[1]=1.0;

		double (*f)(double*,int);
		f=&fun;
		double alpha=0.1;
		int max_step=200;

		myGradientDescendOptimizer<double*> optimizer(varible,numVarible,f,alpha,max_step);
		optimizer.optimize();

		for(int i=0;i<numVarible;i++)
			cout<<varible[i]<<" ";
		cout<<fun(varible,numVarible)<<endl;

		free(varible);
}

#endif
