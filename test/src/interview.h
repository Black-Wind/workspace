//#include <iostream>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include <sstream>
//using namespace std;
//
//
//struct myKeyword{
//	string keyword;
//	int  index;
//};
//
//class myTimeList{
//public:
//	myTimeList(int keywordSize){timeList.resize(keywordSize);times.resize(keywordSize)};
//	void nominal();
//	vector<double> timeList;
//	vector<int>times;
//};
//
//
//void myTimeList::nominal(){
//   for(unsigned i=0;i<timeList.size();i++)
//	   timeList[i]/=times;
//}
//
//bool mysort(myKeyword a,myKeyword b){
//
//	return a.keyword.compare(b.keyword);
//}
//vector <double> BatchQueryExecutionTime(const vector<string> &sql,const vector<double>&times,const vector<string>&keyword)
//{
//
//
//	myTimeList time(keyword.size());
//
//	vector<myKeyword> keywords(keyword.size());
//	///////构造方便查询的关键词序列//////
//	for(unsigned i=0;i<keyword.size();i++)
//		{
//			keywords[i].keyword=keyword[i];
//			keywords[i].index=i;
//		}
//	///////排序//////////////////////
//	sort(keywords,keywords.begin(),keywords.end(),mysort);////////自定义mysort函数/////////
//
//
//	for(unsigned i=0;i<sql.size();i++)
//	{
//		istringstream istr;
//		istr.str(sql[i]);
//
//		string word;
//		while(istr.eof()){
//			istr>>word;
//
//			//////查询word///////
//			int index=binaryFind(keywords);
//			time.timeList[index]+=times[i];
//			time.times[index]++;
//		}
//	time.nominal();
//	}
//	return time.timeList;
//}
//
//
/////////////////////先将查询关键词排序，便于二分查找法，每次得到sql语句中的一个词word，用二分法查找word在不在查询关键词中，在的话便加上这条sql的时间////////////////
////////////////////  时间复杂度 O(N*m*K) ，其中，N是sql语句的数量，m是每一条sql语句平均有m个关键词，K是二分查找法所耗掉的时间//////////////////////////////////

#include <iostream>
using namespace std;

//class A{
//protected:
//	A(){cout<<"good job"<<endl;};
//	~A(){cout<<"sb"<<endl;};
//public :
//	static A* create(){return new A();};
//	void destory(){delete this;};
//};
//class B{
//public :
//	B(){cout<<"good job"<<endl;}
//	~B(){cout<<"sb"<<endl;}
//
//private:
//    void* operator new(size_t t){};     // 注意函数的第一个参数和返回值都是固定的
//    void operator delete(void* ptr){} // 重载了new就需要重载delete
//};



void interview();




