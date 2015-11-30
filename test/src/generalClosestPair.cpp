#include "generalClosestPair.h"

bool sortPointByLastAxis(const Point &p1,const Point &p2)
{
	return p1.axis.back()<p2.axis.back();
}

void GeneralClosestPair::execute(int dimension,vector<Point> &_points)
{
	this->dimension =dimension;
	/**
	 * 在不破坏原数据的前提下
	 */
	vector<Point>points;
	points.insert(points.begin(),_points.begin(),_points.end());
	/**
	 * 先对points按照最后轴大小升序排序
	 */
	sort(points.begin(),points.end(),sortPointByLastAxis);
	/**
	 * action!!
	 */
	Pair closestPair=findClosestPair(dimension,points);

	cout<<"the closest pair:"<<endl;
	closestPair.print();
}




Pair GeneralClosestPair::findClosestPair(int curDimension,vector<Point> &points,\
											double delta)
{
	Pair closestPair;
	int currentFirstDimIndex=this->dimension-curDimension;
	int NUM_POINT=points.size();
	/**
	 * 如果点集只有3个以及3个以下的点
	 */
	if(NUM_POINT<=3)
	{
	for (int i=0;i<NUM_POINT;i++)
		for (int j=0;j<NUM_POINT;j++)
			if(i!=j)
				closestPair.update(points[i], points[j]);
	return closestPair;
	}

	if(curDimension==1&&fabs(delta+1)<1e-6)
	{
		for (int i=0;i<NUM_POINT-1;i++)
			closestPair.update(points[i], points[i+1]);
	return closestPair;
	}

	if(curDimension==1&&fabs(delta+1)>1e+6)
	{
		for(int i=0;i<NUM_POINT;i++)
			for(int j=i+1;j<NUM_POINT;j++)
				if(points[i].axis[currentFirstDimIndex]-points[i].axis[currentFirstDimIndex]<delta)
				closestPair.update(points[i],points[j]);
				else
					break;
	return closestPair;
	}
	/**
	 * 求出低维度 第一个维度值的中间值
	 */
	double midAxis=0.0;
	for (int i=0;i<NUM_POINT;i++)
		midAxis+=points[i].axis[currentFirstDimIndex];
	midAxis/=NUM_POINT;
	/**
	 * 找出分割超平面左边的点lPoints,右边的点rPoints
	 */
	vector<Point>lPoints;
	vector<Point>rPoints;
	for (int i=0;i<NUM_POINT;i++)
		if(midAxis-points[i].axis[currentFirstDimIndex]>0)
			lPoints.push_back(points[i]);
		else
			rPoints.push_back(points[i]);
	/**
	 * 递归求解子问题
	 */
	Pair lPair=findClosestPair(curDimension,lPoints);
	Pair rPair=findClosestPair(curDimension,rPoints);
	Pair minPair=lPair.compare(rPair)?lPair:rPair;
	/**
	 * 找到特定维度值与分割超平面距离小于min的点集midPoints
	 */
	vector<Point>midPoints;
	for (int i=0;i<NUM_POINT;i++)
		if(fabs(midAxis-points[i].axis[currentFirstDimIndex])<minPair.distance)
			midPoints.push_back(points[i]);

	Pair midPair=findClosestPair(curDimension-1,midPoints,minPair.distance);
	closestPair=minPair.compare(midPair)?minPair:midPair;

	return closestPair;
}

void GeneralClosestPair::test()
{
	int dimension=3;
	int NUM_POINT=10;
	int MAX_RANDOM=10;
	vector <Point> points(NUM_POINT);

	srand((unsigned)time(NULL));

	for (int i=0;i<NUM_POINT;i++)
		{	points[i].axis.resize(dimension);
			points[i].dimension=dimension;
			for (int j=0;j<dimension;j++)
				points[i].axis[j]=fabs(MAX_RANDOM*(double)rand()/RAND_MAX);
		}

	///////////output/////////////////////
	for (int i=0;i<NUM_POINT;i++)
			points[i].print();

/////////////////test 1//////////////////////
	// vector <Point> points;
	// Point tmp(dimension);

	// tmp.axis[0]=5.0;
	// tmp.axis[1]=9.0;

	// points.push_back(tmp);

	// tmp.axis[0]=9.0;
	// tmp.axis[1]=3.0;
	// points.push_back(tmp);

	// tmp.axis[0]=2.0;
	// tmp.axis[1]=0.0;
	// points.push_back(tmp);

	// tmp.axis[0]=8.0;
	// tmp.axis[1]=4.0;
	// points.push_back(tmp);

	// tmp.axis[0]=7.0;
	// tmp.axis[1]=4.0;
	// points.push_back(tmp);

	// tmp.axis[0]=9.0;
	// tmp.axis[1]=10.0;
	// points.push_back(tmp);

	// tmp.axis[0]=1.0;
	// tmp.axis[1]=9.0;
	// points.push_back(tmp);

	// tmp.axis[0]=8.0;
	// tmp.axis[1]=2.0;
	// points.push_back(tmp);

	// tmp.axis[0]=0.0;
	// tmp.axis[1]=10.0;
	// points.push_back(tmp);

	// tmp.axis[0]=9.0;
	// tmp.axis[1]=6.0;
	// points.push_back(tmp);

///////////////test 2//////////////////
	// vector <Point> points;
	// Point tmp(dimension);

	// tmp.axis[0]=0.654682;
	// tmp.axis[1]=0.925557;

	// points.push_back(tmp);

	// tmp.axis[0]=0.409382;
	// tmp.axis[1]=0.619391;
	// points.push_back(tmp);

	// tmp.axis[0]=0.891663;
	// tmp.axis[1]=0.888594;
	// points.push_back(tmp);

	// tmp.axis[0]=0.716629;
	// tmp.axis[1]=0.9962;
	// points.push_back(tmp);

	// tmp.axis[0]=0.477721;
	// tmp.axis[1]=0.946355;
	// points.push_back(tmp);

	// tmp.axis[0]=0.925092;
	// tmp.axis[1]=0.81822;
	// points.push_back(tmp);

	// tmp.axis[0]=0.624291;
	// tmp.axis[1]=0.142924;
	// points.push_back(tmp);

	// tmp.axis[0]=0.211332;
	// tmp.axis[1]=0.221507;
	// points.push_back(tmp);

	// tmp.axis[0]=0.293786;
	// tmp.axis[1]=0.691701;
	// points.push_back(tmp);

	// tmp.axis[0]=0.839186;
	// tmp.axis[1]=0.72826;
	// points.push_back(tmp);
///////////////////////////////////////
	execute(dimension,points);
}