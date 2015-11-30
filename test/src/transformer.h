#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define  ATOM_NUMBERS 2;
#define  PI 3.14159265359;


class D3DXVECTOR3{
public:
	D3DXVECTOR3(){};
	D3DXVECTOR3(vector<double>_v){
		x=_v[0];
		y=_v[1];
		z=_v[2];
	}
	double x;
	double y;
	double z;

	D3DXVECTOR3 & operator-(const D3DXVECTOR3 & v2){

		D3DXVECTOR3 tmp;
		tmp.x=x-v2.x;
		tmp.y=y-v2.y;
		tmp.z=z-v2.z;

		return tmp;

	}
	void normalize(){
		double tmpX,tmpY,tmpZ;
		tmpX=x/sqrt(x*x+y*y+z*z);
		tmpY=y/sqrt(x*x+y*y+z*z);
		tmpZ=z/sqrt(x*x+y*y+z*z);
		x=tmpX;
		y=tmpY;
		z=tmpZ;
	}

};

class D3DXMATRIX{
public:
	double m[4][4];
};

class transformer{
public:
	transformer(double * _crd);
	void print();
	void transform(D3DXVECTOR3 ,D3DXVECTOR3,double degree);

private:
	vector<vector<double> > crd;
	vector<vector<double> > Ncrd;
	int atom_num;
};


transformer::transformer(double *_crd){
	atom_num=ATOM_NUMBERS;
	crd.resize(atom_num);
	for (int i=0;i<atom_num;i++)
		for(int j=0;j<3;j++)
			crd[i].push_back(_crd[3*i+j]);
}


void transformer::print()
{

	cout<<"------------------------------"<<endl;
	for(unsigned int i=0;i<Ncrd.size();i++){
//		cout<<i<<" ";
		for(int j=0;j<4;j++)
			cout<<Ncrd[i][j]<<" ";
		cout<<endl;
	}
}



void RotateArbitraryLine(D3DXMATRIX &pOut, D3DXVECTOR3 v1, D3DXVECTOR3 v2, double theta)
{
    double a = v1.x;
    double b = v1.y;
    double c = v1.z;

    D3DXVECTOR3 p = v2 - v1;
    ////////////test////////////
    p.normalize();
    double u = p.x;
    double v = p.y;
    double w = p.z;

    double uu = u * u;
    double uv = u * v;
    double uw = u * w;
    double vv = v * v;
    double vw = v * w;
    double ww = w * w;
    double au = a * u;
    double av = a * v;
    double aw = a * w;
    double bu = b * u;
    double bv = b * v;
    double bw = b * w;
    double cu = c * u;
    double cv = c * v;
    double cw = c * w;

	theta=theta/180.0*PI;

    double costheta = cos(theta);

    double sintheta = sin(theta);

    pOut.m[0][0] = uu + (vv + ww) * costheta;
    pOut.m[0][1] = uv * (1 - costheta) + w * sintheta;
    pOut.m[0][2] = uw * (1 - costheta) - v * sintheta;
    pOut.m[0][3] = 0;

    pOut.m[1][0] = uv * (1 - costheta) - w * sintheta;
    pOut.m[1][1] = vv + (uu + ww) * costheta;
    pOut.m[1][2] = vw * (1 - costheta) + u * sintheta;
    pOut.m[1][3] = 0;

    pOut.m[2][0] = uw * (1 - costheta) + v * sintheta;
    pOut.m[2][1] = vw * (1 - costheta) - u * sintheta;
    pOut.m[2][2] = ww + (uu + vv) * costheta;
    pOut.m[2][3] = 0;

    pOut.m[3][0] = (a * (vv + ww) - u * (bv + cw)) * (1 - costheta) + (bw - cv) * sintheta;
    pOut.m[3][1] = (b * (uu + ww) - v * (au + cw)) * (1 - costheta) + (cu - aw) * sintheta;
    pOut.m[3][2] = (c * (uu + vv) - w * (au + bv)) * (1 - costheta) + (av - bu) * sintheta;
    pOut.m[3][3] = 1;
}


void transformer::transform(D3DXVECTOR3 v1,D3DXVECTOR3 v2,double degree){

	D3DXMATRIX matrix;


	////////////transfom/////////////////
	RotateArbitraryLine(matrix,v1,v2,degree);

	Ncrd.resize(atom_num);
	for(unsigned int i=0;i<crd.size();i++)
	{

		for(unsigned int j=0;j<4;j++)
		{
			double sum=0.0;
			for(unsigned int k=0;k<4;k++)
				sum+=matrix.m[k][j]*crd[i][k];
			Ncrd[i].push_back(sum);
		}
	}


}


#endif
