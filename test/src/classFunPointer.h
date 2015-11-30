#ifndef CLASSFUNPOINTER_H
#define CLASSFUNPOINTER_H

#include <iostream>
#include <stdio.h>

using namespace std;

class A{

public:
	int i;
	void fun(string s){cout<<s<<endl;}
	void fun1(string s){cout<<endl;}
	static void func(string s){cout<<s<<endl;}

};



/////////test1 成员函数指针的普通测试//////////////
inline void classFunPointerTest1()
{
	A a;
	void(A::*p)(string s);
	p=&A::fun;   /// not p=&(A::fun)

	(a.*p)("hello girl");
}
inline void func(string s){
	cout<<s<<endl;
}
////////////////test 2 传参数/////////////////
inline void Test(A &a,void (A::* p)(string s)){

	(a.*p)("i love you");
}



inline void classFunPointerTest2()
{
	void (A::*p)(string s);
	p=&A::fun;
	A a;
	Test(a,p);
}

///////test 3 测试 函数地址/////////////////////////
inline void classFunPointerTest3()
{
	A a,b;

//  error ISO C++ forbids taking the address of a bound member function to form a apointer to member function


	printf("%x\n",func);

}


#endif
