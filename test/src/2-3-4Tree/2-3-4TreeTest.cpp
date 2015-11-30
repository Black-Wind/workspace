#include "2-3-4TreeTest.h"


void tree234Test::simpleTest()
{
	LLRBTree<long int> tree234;
	tree234.insert(10);
	tree234.insert(20);
	tree234.insert(40);
	// tree234.insert(90);
	// tree234.insert(50);
	// tree234.insert(80);
	// tree234.insert(60);
	// tree234.insert(70);
	// tree234.insert(95);

	// tree234.insert(20);
	// tree234.insert(30);
	// tree234.insert(40);
	// tree234.insert(60);
	// tree234.insert(70);
	// tree234.insert(80);
	// tree234.insert(45);
	// tree234.insert(50);

	tree234.orderTraversal();
	tree234.printPreTraversal();
	tree234.printPostTraversal();

	tree234.remove(70);
	// tree234.remove(20);
	// tree234.remove(30);
	// tree234.remove(0);
	tree234.orderTraversal();
	tree234.printPreTraversal();
	tree234.printPostTraversal();
}

void tree234Test::executeTest()
{
	cout<<"测试开始"<<endl;
	/**
	 *初始化内存
	 */

	LLRBTree<long int> tree234;

	tree234.setOutput(false);

	long int key,i=0;
	std::vector<long int> keys;
	ifstream input("2-3-4树测试数据.txt");
	while(input>>key)
	{
		i++;
		if(i%1000000==0)cout<<i<<endl;
		keys.push_back(key);
	}
	clock_t start=clock();
	unsigned int size=keys.size();
	for(unsigned i=0;i<size;i++)
	{
		tree234.insert(keys[i]);
	}
	clock_t finish=clock();
	double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"建树花费了"<<duration<<"s"<<endl;
	cout<<keys.size()<<endl;
	keys.clear();
	input.close();




	// ifstream input("2-3-4树测试数据.txt");

	// while(input>>key)
	// {
	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==10000000)
	// 		break;
	// }
	// clock_t start=clock();
	// unsigned int size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// clock_t finish=clock();
	// double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==20000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==30000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==40000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();
	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==50000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();
	// 	while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==60000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==70000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==80000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==90000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// while(input>>key)
	// {

	// 	keys.push_back(key);
	// 	i++;
	// 	if(i%1000000==0)
	// 		{
	// 			cout<<i<<endl;
	// 		}
	// 	if(i==100000000)
	// 		break;
	// }
	// start=clock();
	// size=keys.size();
	// for(unsigned j=0;j<size;j++)
	// {
	// 	tree234.insert(keys[j]);
	// }
	// finish=clock();
	// duration+=(double)(finish-start)/CLOCKS_PER_SEC;
	// cout<<"times:"<<duration<<endl;
	// keys.clear();

	// cout<<"建树花费了"<<duration<<"s"<<endl;
	// input.close();


	start=clock();
	tree234.printPreTraversal();
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"遍历花费了"<<duration<<"s"<<endl;

	input.open("2-3-4树删除数据.txt");
	while(input>>key)
	{
		keys.push_back(key);
	}
	start=clock();
	size=keys.size();
	for(unsigned j=0;j<size;j++)
	{
		tree234.remove(keys[j]);
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"删除花费了"<<duration<<"s"<<endl;
	cout<<keys.size()<<endl;
	keys.clear();
	input.close();

}