#include <ctime>
#include <cstdio>
#include <fstream>
#include "Treap.h"
#include "TreapTest.h"



void simpleTest()
{
/**
 * 简单测试
 */
clock_t start=clock();


Treap<long int>treap;

treap.insert(new Item<long int>(50340,"ju45","ri4py33f","c8vm2p021k","8ood0gt2m2xmaybicp30dc1rvg8fabqfrwodrlik"));
treap.insert(new Item<long int>(134851,"ogv0","rjbxkvoa","rvftgix5ge","a0b770frg6gyqq8lugb538qj54qd2302l3atkj3p"));
Item<long int>item(535103,"nvon","2mmsc25z","2al8ret1jf","rqfuq0k8sduvemz9cqdt1ginj1etfjqjul62zpa9");
treap.insert(item);
// treap.intervalKeyRemove(100000,600000);
// treap.print();
// cout<<endl;
treap.insert(new Item<long int>(811900,"17k7","n57xafut","efvokswscp","fuakc6pg0s459izet3uki82lcw3gvtcaw4rk96oj"));
treap.insert(new Item<long int>(811900,"17k7","n57xafut","efvokswscp","fuakc6pg0s459izet3uki82lcw3gvtcaw4rk96oj"));
treap.print();
cout<<endl;
// treap.searchByKey(item);
// cout<<endl;

// treap.singleKeyRemove(item);
// cout<<endl;
// treap.print();
// cout<<endl;
// treap.searchByKey(item);
// cout<<endl;
treap.intervalKthRemove(2,3);
// treap.intervalKeyRemove(5000,100000);
// treap.kthRemove(2);
treap.print();
cout<<endl;


clock_t finish=clock();
double duration=(double)(finish-start)/CLOCKS_PER_SEC;
cout<<"运行了"<<duration<<"s"<<endl;


}



void executeTest1()
{
	cout<<"测试数据1"<<endl;
	/**
	 *初始化内存
	 */
	// freopen("测试数据1.txt","r",stdin);
	ifstream input("测试数据1.txt");
	Treap<long int>treap;
	long int key;
	string s1,s2,s3,s4;
	long int i=0;

	std::vector<Item<long int> > items;
	while(input>>key>>s1>>s2>>s3>>s4)
	{
		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
	}
	clock_t start=clock();
	unsigned int size=items.size();
	for(unsigned i=0;i<size;i++)
	{
		treap.insert(items[i]);
	}
	clock_t finish=clock();
	double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"建树花费了"<<duration<<"s"<<endl;
	items.clear();
	input.close();
	/**
	 * 简单删除
	 */
	// freopen("测试数据1中待删除的int整型集合数据11.txt","r",stdin);
	input.open("测试数据1中待删除的int整型集合数据11.txt");
	start=clock();
	while(input>>key)
	{
		// cout<<key<<endl;
		// if(i==10000)break;
		Item<long int>item(key,"","","","");
		// cout<<++i<<"    ";
		// item.print();
		// cout<<endl;
		treap.singleKeyRemove(item);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"简单删除花费了"<<duration<<"s"<<endl;
	input.close();
	/**
	 *kth删除和[ath,bth]删除
	 */
	start=clock();
	treap.kthRemove(10000);
	treap.intervalKthRemove(20000,30000);
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"kth以及kth区间删除花费了"<<duration<<"s"<<endl;
		/**
		 *key区间删除
		 */
		start=clock();
		treap.intervalKeyRemove(1200,140200);
		treap.intervalKeyRemove(200010,493029);
		treap.intervalKeyRemove(528394,763748);
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		cout<<"key区间删除花费了"<<duration<<"s"<<endl;
	/**
	 * 批量插入
	 */
	// freopen("测试数据1中待删除的int整型集合数据11.txt","r",stdin);
	input.open("测试数据1中待插入数据.txt");
	start=clock();
	while(input>>key>>s1>>s2>>s3>>s4)
	{
		Item<long int>item(key,s1,s2,s3,s4);
		treap.insert(item);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"批量插入花费了"<<duration<<"s"<<endl;
	input.close();

	/**
	 * 查询
	 */
	input.open("测试数据1中待查询的int整数型集合数据13.txt");
	start=clock();
	while(input>>key)
	{
		Item<long int>item(key,"","","","");
		treap.searchByKey(item);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"查询花费了"<<duration<<"s"<<endl;
	input.close();
}
void executeTest2()
{
	cout<<"测试数据2"<<endl;
	/**
	 *初始化内存
	 */
	// freopen("测试数据1.txt","r",stdin);
	ifstream input("测试数据2.txt");
	Treap<long int>treap;
	long int key;
	string s1,s2,s3,s4;
	long int i=0;
	std::vector<Item<long int> > items;
	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==1000000)
			break;
	}
	clock_t start=clock();
	unsigned int size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	clock_t finish=clock();
	double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==2000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==3000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==4000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==5000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();
	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==6000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==7000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==8000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==9000000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();


	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		if(i==9500000)
			break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	while(input>>key>>s1>>s2>>s3>>s4)
	{

		Item<long int>item(key,s1,s2,s3,s4);
		items.push_back(item);
		i++;
		if(i%10000==0)
			{
				cout<<i<<" ";
				item.print();
				cout<<endl;
			}
		// if(i==9900000)
		// 	break;
	}
	start=clock();
	size=items.size();
	for(unsigned j=0;j<size;j++)
		treap.insert(items[j]);
	finish=clock();
	duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"times:"<<duration<<endl;
	items.clear();

	cout<<"建树花费了"<<duration<<"s"<<endl;


	input.close();
	// clock_t start=clock();
	// while(input>>key>>s1>>s2>>s3>>s4)
	// {
	// 	if(i==1000000)break;
	// 	Item<long int>item(key,s1,s2,s3,s4);
	// 	cout<<++i<<"    ";
	// 	item.print();
	// 	cout<<endl;
	// 	treap.insert(item);
	// }
	// clock_t finish=clock();
	// double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"建树花费了"<<duration<<"s"<<endl;

	// input.close();
	/**
	 * 简单删除
	 */
	// freopen("测试数据1中待删除的int整型集合数据11.txt","r",stdin);
	input.open("测试数据2中待删除的int整型集合数据11.txt");
	start=clock();
	while(input>>key)
	{
		// cout<<key<<endl;
		// if(i==10000)break;
		Item<long int>item(key,"","","","");
		// cout<<++i<<"    ";
		// item.print();
		// cout<<endl;
		treap.singleKeyRemove(item);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"简单删除花费了"<<duration<<"s"<<endl;
	input.close();
	/**
	 *kth删除和[ath,bth]删除
	 */
	start=clock();
	treap.kthRemove(100000);
	treap.intervalKthRemove(200000,300000);
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"kth以及kth区间删除花费了"<<duration<<"s"<<endl;
		/**
		 *key区间删除
		 */
		start=clock();
		treap.intervalKeyRemove(1200,783200);
		treap.intervalKeyRemove(2100000,6593029);
		treap.intervalKeyRemove(7283940,8537480);
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		cout<<"key区间删除花费了"<<duration<<"s"<<endl;
	/**
	 * 批量插入
	 */
	// freopen("测试数据1中待删除的int整型集合数据11.txt","r",stdin);
	input.open("测试数据2中待插入数据.txt");
	start=clock();
	while(input>>key>>s1>>s2>>s3>>s4)
	{
		Item<long int>item(key,s1,s2,s3,s4);
		treap.insert(item);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"批量插入花费了"<<duration<<"s"<<endl;
	input.close();

	/**
	 * 查询
	 */
	input.open("测试数据2中待查询的int整数型集合数据13.txt");
	start=clock();
	while(input>>key)
	{
		Item<long int>item(key,"","","","");
		treap.searchByKey(item);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"查询花费了"<<duration<<"s"<<endl;
	input.close();
}