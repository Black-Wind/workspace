#include "ArticulationPoint.h"


void ArticulationPointRevealer::test()
{


	clock_t start=clock();

	Init();
	dfs(ROOT);
	clock_t finish=clock();
	double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"运行了"<<duration<<"s"<<endl;
	print();
}


void ArticulationPointRevealer::Init()
{
	/*
		Matrix  初始化
 	*/
 	Matrix.resize(NUM_POINT+1);
 	for(int i=0;i<=NUM_POINT;i++)
 		Matrix[i].resize(NUM_POINT+1);

 	adjacencyLists.resize(NUM_POINT+1);
	/*
		input
	 */
 	cout<<"<<<1"<<endl;
	scanInput();
	cout<<"<<<2"<<endl;
	isVisited.resize(NUM_POINT+1);
	dVector.resize(NUM_POINT+1);
	low.resize(NUM_POINT+1);

	// d=0;
}
void ArticulationPointRevealer::scanInput()
{
	freopen(inputFileName.c_str(),"r",stdin);
	char tmpChar;
	int point1,point2;

	while(cin>>tmpChar)//'('
	{
		cin>>point1;
		cin>>tmpChar;	//','
		cin>>point2;
		cin>>tmpChar;	//')'

		Matrix[point1][point2]=Matrix[point2][point1]=true;

		adjacencyLists[point1].push_back(point2);
		adjacencyLists[point2].push_back(point1);
	}

}
void ArticulationPointRevealer::print()
{
	cout<<ArticulationPoint.size();
	cout<<"个关节点:"<<endl;;
	set<int>::iterator iter;
	for (iter=ArticulationPoint.begin();iter!=ArticulationPoint.end();iter++)
			cout<<*iter<<" ";
		cout<<endl;

}


/**
 * 基于深度优化算法的关节点搜索算法
 * @param  pointIndex 节点编号
 * @return            当前节点的low值
 *
 * low[v]=min {	dVector[v];	min(low[w]|w是v的一个子女);min(dVector[x]|(v,x)是一条回边)	}
 * v是关节点当且仅当 v存在一个子节点y,使得low[y]>=dVector[v]
 */
int ArticulationPointRevealer::dfs(int pointIndex)
{
	/*
		这是条回边
	 */
	if(isVisited[pointIndex])
		return dVector[pointIndex];
	/*
		访问新节点
	 */
	dVector[pointIndex]=++d;
	isVisited[pointIndex]=true;
	int curD=dVector[pointIndex];

	int minSub=INFINITY;
	for( int i=0;i<adjacencyLists[pointIndex].size();i++)
		if(adjacencyLists[pointIndex][i]!=-1)
		{
			int next=adjacencyLists[pointIndex][i];
			adjacencyLists[pointIndex][i]=-1;
			for(int j=0;j<adjacencyLists[next].size();j++)
				if(adjacencyLists[next][j]==pointIndex)
				{
					adjacencyLists[next][j]=-1;
					break;
				}

			int lowSub=dfs(next);
			/**
			 *	保存关节点
			 */
			if(lowSub>=curD)
				ArticulationPoint.insert(pointIndex);

			minSub=minSub<lowSub?minSub:lowSub;
		}
	int low=minSub<curD?minSub:curD;
	return low;
}


/*
	非递归版本
 */
void ArticulationPointRevealer::ndfs(int node)
{
	stack.push(node);
	dVector[node]=++d;
	isVisited[node]=true;
	// int curD=dVector[node];
	low[node]=d;
	int i;

	while(!stack.empty())
	{
		node=stack.top();



		for(i=1;i<=NUM_POINT;i++)
			if(Matrix[node][i])
			{
				Matrix[node][i]=Matrix[i][node]=false;
				if(isVisited[i])
					low[node]=low[node]<dVector[i]?low[node]:dVector[i];
				else
				{
					stack.push(i);
					dVector[i]=++d;
					isVisited[i]=true;
					low[i]=d;
					break;
				}
			}

		if(i==NUM_POINT+1)
			{
				stack.pop();
				if (!stack.empty())
				{
					/* code */
					int top=stack.top();
					if(low[node]>=dVector[top])
						ArticulationPoint.insert(top);
					low[top]=low[top]<low[node]?low[top]:low[node];
				}
			}
	}


}
