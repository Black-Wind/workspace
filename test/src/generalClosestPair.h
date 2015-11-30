#ifndef GENERALCLOESTPAIR_H
#define GENERALCLOESTPAIR_H


#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

class Point{
public:
	Point(){dimension=0;}
	Point(int _dimension):dimension(_dimension)
	{
		axis.resize(_dimension);
	}

	void print()
	{
		cout<<"(";
		for (int i=0;i<axis.size();i++)
		{
			cout<<axis[i];
			if(i!=axis.size()-1)
				cout<<",";
		}
		cout<<")"<<endl;
	}

	void operator =(Point &tmp)
	{
		dimension=tmp.dimension;
		axis.resize(dimension);
		for (int i=0;i<dimension;i++)
			axis[i]=tmp.axis[i];
	}

	vector <double> axis;
	int dimension;
};

inline double distanceTwoPoints(const Point &point1,const Point&point2)
{
	double sum=0.0;
	for (int i=0;i<point1.dimension;i++)
	{
		double tmp=point1.axis[i]-point2.axis[i];
		sum+=tmp*tmp;
	}
	return sqrt(sum);
}

class Pair
{
public:
	Pair(){distance=INFINITY;}
	Pair(Point p1,Point p2)
	{
		dest1=p1;
		dest2=p2;
		distance=distanceTwoPoints(p1,p2);
	}

	bool compare(const Pair &pair)
	{
		return this->distance<pair.distance;

	}
	bool update(const Pair &pair)
	{
		return this->update(pair.dest1,pair.dest2);
	}
	bool update(const Point &p1,const Point &p2)
	{
		bool isUpdated=false;
		double _distance=distanceTwoPoints(p1,p2);
		if(_distance<distance)
		{
			Pair tmp(p1,p2);
			*this=tmp;
			isUpdated=true;
		}
		return isUpdated;
	}
	void operator=(Pair&tmp)
	{
		dest1=tmp.dest1;
		dest2=tmp.dest2;
		distance=tmp.distance;

	}
	void print()
	{
		cout<<"distance:"<<distance<<endl;
		cout<<"the points:"<<endl;
		dest1.print();
		dest2.print();
	}
	Point 	dest1;
	Point 	dest2;
	double 	distance;
};

class GeneralClosestPair{
public:
	void test();
	void execute(int dimension,vector<Point> &_points);
private:
	Pair findClosestPair(int curDimension,vector<Point> &points,double delta=-1);
	int dimension;


};


#endif
