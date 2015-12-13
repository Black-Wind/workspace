#pragma once
#include "../global.h"

#define BLACK0 				0
#define BLACK1 				1
#define BLACK2 				2
#define BLACK3 				3
#define BLACK4 				4
#define BLACK  				5
#define WHITE  				9
#define LIGHT   			6
#define ILLUMINATED 		7
#define FORBIDDENED 		8

#define ERROR   			10
#define UPDATEDANDTRUE		11
#define UNUPDATEDANDTREU	12
#define	FINISHED 			13
#define UNFINSHED			14
#define NOERROR				15

#define WHITELISTUSED		16

class Akari
{
public:
	Akari(vector<vector<int> > &_map)
	{
		realRow=_map.size();
		row=realRow+2;
		realCol=_map[0].size();
		col=realCol+2;
		map.resize(row);
		newLine(map[0]);
		newLine(map[row-1]);

		for (int i = 0; i < realRow; ++i)
		{
			/* code */
			newLine(map[i+1]);

			for(int j=0;j<realCol;j++)
				map[i+1][j+1]=_map[i][j];
		}
		/**
		 * debug
		 */
		 print(map);
	}
	void excute()
	{
		debug=false;
		preproccess();
		pattern_match_loop(map);
		local_search(map);
		// print(map);
		Ndebug(map);
	}
private:
	bool debug;
	int col,row;
	int realCol,realRow;
	vector<vector<int> > map;
	stack<vector<vector<int> > >map_stack;


	vector<string> slover;
	int local_search(vector<vector <int> >&_map)
	{
		int result=NOERROR;
		deque<vector<int> >white_list;
		getWhiteList(_map,white_list);

		if(!white_list.empty())result=ERROR;
		while(!white_list.empty())
		{
			int m=white_list[0][0],n=white_list[0][1];
			white_list.pop_front();

			/**
			 * presume [m,n]
			 * brandh search
			 */
			vector<vector<int> >_cmap;
			/**
			 * copy
			 */
			copy(_cmap,_map);
			int result_presume=branch_search(_cmap,m,n);

			if (result_presume==UNFINSHED)
				result_presume=local_search(_cmap);

			if(result_presume==FINISHED)
			{
				result=FINISHED;
				break;
			}
			if(result_presume==ERROR)
				forbidden(_map, m,n);
		}
		return result;
	}

	void getWhiteList(vector<vector <int> >&_map,deque<vector<int> >& white_list)
	{
		vector<vector<int> > temp_map;
		copy(temp_map, _map);
		for (int i = 0; i < row; ++i)
		{
			/* code */
			for (int j = 0; j < col; ++j)
			{
				/* code */
				if(isBlack0_4(_map,i,j))
				{
					if(_map[i-1][j]==WHITE)
					{
						push_back_white_list(_map,white_list,i-1,j,temp_map);
					}
					if(_map[i+1][j]==WHITE)
					{
						push_back_white_list(_map,white_list,i+1,j,temp_map);
					}
					if(_map[i][j-1]==WHITE)
					{
						push_back_white_list(_map,white_list,i,j-1,temp_map);
					}
					if(_map[i][j+1]==WHITE)
					{
						push_back_white_list(_map,white_list,i,j+1,temp_map);
					}

				}

			}
		}

		for (int i = 0; i < row; ++i)
		{
			/* code */
			for (int j = 0; j < col; ++j)
			{
				/* code */
				if(_map[i][j]==WHITE)
				{
					push_back_white_list(_map,white_list,i,j,temp_map);
				}
			}
		}
	}
	void push_back_white_list(vector<vector <int> >&_map,deque<vector<int> >& white_list,\
							int i,int j,vector<vector <int> >&temp_map)
	{
		if(temp_map[i][j]!=WHITELISTUSED)
		{
			vector<int>tempv;
			tempv.push_back(i);
			tempv.push_back(j);
			white_list.push_back(tempv);
			temp_map[i][j]=WHITELISTUSED;
		}
	}
	int branch_search(vector<vector <int> >& _map,int m,int n)
	{
		if(debug)
			cout<<"branch_search:"<<"["<<m<<","<<n<<"]"<<endl;
		int flag;
		put_light(_map,m,n);

		flag=pattern_match_loop(_map);

		if(flag==ERROR)return ERROR;
		if(isDone(_map))
		{
			wirte(_map);
			return FINISHED;
		}
		else return UNFINSHED;
	}
	void preproccess()
	{
		for (int i = 0; i < row; ++i)
		{
			/* code */
			for (int j = 0; j < col; ++j)
			{
				if(map[i][j]==BLACK0)
				{
					forbidden_black_square(map,i,j);
					if(debug)
						cout<<"pre:"<<"["<<i<<","<<j<<"]"<<endl;

				}
				else if(map[i][j]==BLACK4)
				{
					put_light_around_black_square(map,i,j);
					if(debug)
						cout<<"pre:"<<"["<<i<<","<<j<<"]"<<endl;
				}
			}
		}
	}
	bool forbidden(vector<vector <int> >&_map,int i,int j)
	{
		if(_map[i][j]==WHITE)
		 _map[i][j]=FORBIDDENED;
		else
		{
			cout<<"forbidden error:"<<_map[i][j]<<endl;
			return false;
		}
		return true;
	}
	bool forbidden_black_square(vector<vector<int> >&_map,int i,int j)
	{
		bool flag=false;
		if(_map[i-1][j]==WHITE)flag|=forbidden(_map,i-1,j);
		if(_map[i+1][j]==WHITE)flag|=forbidden(_map,i+1,j);
		if(_map[i][j-1]==WHITE)flag|=forbidden(_map,i,j-1);
		if(_map[i][j+1]==WHITE)flag|=forbidden(_map,i,j+1);
		return flag;
	}
	bool put_light_around_black_square(vector<vector<int> >&_map,int i,int j)
	{
		bool flag=false;
		if(_map[i-1][j]==WHITE)flag|=put_light(_map,i-1,j);
		if(_map[i+1][j]==WHITE)flag|=put_light(_map,i+1,j);
		if(_map[i][j-1]==WHITE)flag|=put_light(_map,i,j-1);
		if(_map[i][j+1]==WHITE)flag|=put_light(_map,i,j+1);
		return flag;
	}
	int pattern_match_loop(vector <vector<int> >&_map)
	{
		bool flag=true;
		while(flag)
		{
			if(error_patter_match(_map))return ERROR;
			flag=pattern_match(_map);
		}
		return NOERROR;
	}
	bool error_patter_match(vector<vector<int> >&_map)
	{
		for (int m = 0; m < row; ++m)
		{
			/* code */
			for (int n = 0; n < col; ++n)
			{
				/* code */
				if(isBlack0_4(_map,m,n))
				{
					int white_num=0,light_num=0;

					if(_map[m-1][n]==WHITE)white_num++;
					else if(_map[m-1][n]==LIGHT)light_num++;

					if(_map[m+1][n]==WHITE)white_num++;
					else if(_map[m+1][n]==LIGHT)light_num++;

					if(_map[m][n-1]==WHITE)white_num++;
					else if(_map[m][n-1]==LIGHT)light_num++;

					if(_map[m][n+1]==WHITE)white_num++;
					else if(_map[m][n+1]==LIGHT)light_num++;

					if(light_num+white_num<_map[m][n])
					{
						if(debug)cout<<"black need error:"<<"["<<m<<","<<n<<"]"<<endl;
						return true;
					}
				}
				if(_map[m][n]==FORBIDDENED)
				{
					int light_source_num=0;
					for (int i = 1; ; ++i)
					{
						/* code */
						if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
						if(_map[m+i][n]==WHITE)
						{
							light_source_num++;

						}
					}
					for (int i = -1; ; --i)
					{
						/* code */
						if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
						if(_map[m+i][n]==WHITE)
						{
							light_source_num++;

						}
					}
					for (int i = 1; ; ++i)
					{
						/* code */
						if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
						if(_map[m][n+i]==WHITE)
						{
							light_source_num++;

						}
					}
					for (int i = -1; ; --i)
					{
						/* code */
						if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
						if(_map[m][n+i]==WHITE)
						{
							light_source_num++;

						}

					}
					if(light_source_num==0)
					{
						if(debug)
							cout<<"forbidden error:"<<"["<<m<<","<<n<<"]"<<endl;
						return true;
					}
				}
			}
		}
		return false;
	}
	bool pattern_match(vector<vector<int> >&_map)
	{
		for (int i = 0; i < row; ++i)
		{
			/* code */
			for (int j = 0; j < col; ++j)
			{
 			 	if(_map[i][j]>=BLACK0&&_map[i][j]<=BLACK4)
 			 	{
 			 		if(pattern1_match(_map,i,j))return true;
 			 		// if(pattern4_match(_map,i,j))return true;
 			 	}
 			 	if(_map[i][j]==WHITE&&pattern2_match(_map,i,j))return true;
 			 	if(_map[i][j]==FORBIDDENED)
 			 	{
 			 		if(pattern2_match(_map,i,j))return true;
 			 		if(pattern3_match(_map,i,j))return true;
 			 	}
			}
		}
		return false;
	}
	bool pattern1_match(vector<vector<int> > &_map,int m,int n)
	{

		int white_num=0,light_num=0;

		if(_map[m-1][n]==WHITE)white_num++;
		else if(_map[m-1][n]==LIGHT)light_num++;

		if(_map[m+1][n]==WHITE)white_num++;
		else if(_map[m+1][n]==LIGHT)light_num++;

		if(_map[m][n-1]==WHITE)white_num++;
		else if(_map[m][n-1]==LIGHT)light_num++;

		if(_map[m][n+1]==WHITE)white_num++;
		else if(_map[m][n+1]==LIGHT)light_num++;

		if(white_num+light_num==_map[m][n])
		{
			if(put_light_around_black_square(_map,m,n))
			{
				if(debug)
					cout<<"pattern1_match:"<<"["<<m<<","<<n<<"]"<<endl;
				return true;
			}
		}

		if(light_num==_map[m][n])
		{
			if(forbidden_black_square(_map,m,n))
			{
				if(debug)
					cout<<"forbidden_black_square:"<<"["<<m<<","<<n<<"]"<<endl;
				return true;
			}
		}
		if(white_num==_map[m][n]-light_num+1)
			if(pattern4_match(_map,m,n))
			{

				return true;
			}
		return false;
	}
	bool pattern2_match(vector<vector<int> > &_map,int m,int n)
	{
		int sourceI,sourceJ,light_source_num=0;
		bool flag=false;
		for (int i = 0; ; ++i)
		{
			/* code */
			if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
			if(_map[m+i][n]==WHITE)
			{
				light_source_num++;
				sourceI=m+i;
				sourceJ=n;
			}
		}
		for (int i = -1; ; --i)
		{
			/* code */
			if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
			if(_map[m+i][n]==WHITE)
			{
				light_source_num++;
				sourceI=m+i;
				sourceJ=n;
			}
		}
		for (int i = 1; ; ++i)
		{
			/* code */
			if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
			if(_map[m][n+i]==WHITE)
			{
				light_source_num++;
				sourceI=m;
				sourceJ=n+i;
			}
		}
		for (int i = -1; ; --i)
		{
			/* code */
			if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
			if(_map[m][n+i]==WHITE)
			{
				light_source_num++;
				sourceI=m;
				sourceJ=n+i;
			}

		}
		if(light_source_num==1)
		{
			// cout<<_map[m][n+1]<<endl;
			flag|=put_light(_map,sourceI,sourceJ);
		}
		if(flag&&debug)
		 	cout<<"pattern2_match:"<<"["<<m<<","<<n<<"],"<<\
		 			"source:"<<"["<<sourceI<<","<<sourceJ<<"]"<<endl;
		return flag;
	}
	bool pattern3_match(vector<vector<int> > &_map,int m,int n)
	{
		bool flag=false;
		int row_off,col_off;
		int row_source_num=0,col_source_num=0;
		for (int i = 1; ; ++i)
		{
			/* code */
			if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
			if(_map[m+i][n]==WHITE)
			{
				row_source_num++;
				row_off=i;
			}
		}
		for (int i = -1; ; --i)
		{
			/* code */
			if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
			if(_map[m+i][n]==WHITE)
			{
				row_source_num++;
				row_off=i;
			}
		}
		for (int i = 1; ; ++i)
		{
			/* code */
			if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
			if(_map[m][n+i]==WHITE)
			{
				col_source_num++;
				col_off=i;
			}
		}
		for (int i = -1; ; --i)
		{
			/* code */
			if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
			if(_map[m][n+i]==WHITE)
			{
				col_source_num++;
				col_off=i;
			}

		}

		if(row_source_num==1&&col_source_num==1)
			if(_map[m+row_off][n+col_off]==WHITE&&!is_have_block(_map,m+row_off,n+col_off,m,n+col_off)\
				&&!is_have_block(_map,m+row_off,n+col_off,m+row_off,n))
			{
				forbidden(_map, m+row_off, n+col_off);
				flag=true;
			}
		if(flag&&debug)
		 	cout<<"pattern3_match:"<<"["<<m<<","<<n<<"]"<<endl;
		return flag;
	}
	bool isBlack(vector<vector<int> > &_map,int m,int n)
	{
		return _map[m][n]>=BLACK0&&_map[m][n]<=BLACK;
	}
	bool isBlack0_4(vector<vector<int> > &_map,int m,int n)
	{
		return _map[m][n]>=BLACK0&&_map[m][n]<=BLACK4;
	}
	bool is_have_block(vector<vector<int> > &_map,int m,int n,int i,int j)
	{
		int max,min;
		if(m==i)
		{
			max=n>j?n:j;
			min=n<j?n:j;
			for (int i = min; i <=max; ++i)
			{
				/* code */
				if(isBlack(_map,m,i))return true;
			}
		}
		else if(n==j)
		{
			max=m>i?m:i;
			min=m<i?m:i;
			for (int i = min; i <=max; ++i)
			{
				/* code */
				if(isBlack(_map,i,n))return true;
			}
		}
		return false;
	}
	bool pattern4_match(vector<vector<int> > &_map,int m,int n)
	{
		bool flag=false;
		if(_map[m-1][n]==WHITE&&_map[m][n-1]==WHITE&&_map[m-1][n-1]==WHITE)
		{
			forbidden(_map, m-1, n-1);
			if(debug)
				cout<<"pattern4_match:"<<"["<<m<<","<<n<<"]"<<","<<"forbidden:["<<m-1<<","<<n-1<<"]"<<endl;
			flag=true;
		}
		if(_map[m-1][n]==WHITE&&_map[m][n+1]==WHITE&&_map[m-1][n+1]==WHITE)
		{
			forbidden(_map, m-1, n+1);
			if(debug)
				cout<<"pattern4_match:"<<"["<<m<<","<<n<<"]"<<","<<"forbidden:["<<m-1<<","<<n+1<<"]"<<endl;
			flag=true;
		}
		if(_map[m+1][n]==WHITE&&_map[m][n-1]==WHITE&&_map[m+1][n-1]==WHITE)
		{
			forbidden(_map, m+1, n-1);
			if(debug)
				cout<<"pattern4_match:"<<"["<<m<<","<<n<<"]"<<","<<"forbidden:["<<m+1<<","<<n-1<<"]"<<endl;
			flag=true;
		}
		if(_map[m+1][n]==WHITE&&_map[m][n+1]==WHITE&&_map[m+1][n+1]==WHITE)
		{
			forbidden(_map, m+1, n+1);
			if(debug)
				cout<<"pattern4_match:"<<"["<<m<<","<<n<<"]"<<","<<"forbidden:["<<m+1<<","<<n+1<<"]"<<endl;
			flag=true;
		}
		return flag;
	}


	bool put_light(vector<vector<int> > &_map,int m,int n)
	{
		if(_map[m][n]!=WHITE)
		{
			cout<<"light-on error:"<<_map[m][n]<<endl;
			return false;
		}
		_map[m][n]=LIGHT;
		for (int i = 1; ; ++i)
		{
			/* code */
			if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
			if(_map[m+i][n]==WHITE||_map[m+i][n]==FORBIDDENED)_map[m+i][n]=ILLUMINATED;
			if(_map[m+i][n]==LIGHT)return false;
		}
		for (int i = -1; ; --i)
		{
			/* code */
			if(_map[m+i][n]>=BLACK0&&_map[m+i][n]<=BLACK)break;
			if(_map[m+i][n]==WHITE||_map[m+i][n]==FORBIDDENED)_map[m+i][n]=ILLUMINATED;
			if(_map[m+i][n]==LIGHT)return false;
		}
		for (int i = 1; ; ++i)
		{
			/* code */
			if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
			if(_map[m][n+i]==WHITE||_map[m][n+i]==FORBIDDENED)_map[m][n+i]=ILLUMINATED;
			if(_map[m][n+i]==LIGHT)return false;
		}
		for (int i = -1; ; --i)
		{
			/* code */
			if(_map[m][n+i]>=BLACK0&&_map[m][n+i]<=BLACK)break;
			if(_map[m][n+i]==WHITE||_map[m][n+i]==FORBIDDENED)_map[m][n+i]=ILLUMINATED;
			if(_map[m][n+i]==LIGHT)return false;
		}

		return true;
	}
	bool check(vector<vector<int> >&_map)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				/* code */
				if(_map[i][j]>=BLACK0&&map[i][j]<=BLACK4)
				{
					if(!check_black_square(_map,i,j))
						return false;
				}

			}

		}
		return true;
	}
	bool check_black_square(vector<vector<int> > &_map,int i, int j)
	{
		int light_num=0,used=0;
		if(_map[i-1][j]==LIGHT)light_num++;
		else if(_map[i-1][j]!=WHITE)used++;

		if(_map[i+1][j]==LIGHT)light_num++;
		else if(_map[i+1][j]!=WHITE)used++;

		if(_map[i][j-1]==LIGHT)light_num++;
		else if(_map[i][j-1]!=WHITE)used++;

		if(_map[i][j+1]==LIGHT)light_num++;
		else if(_map[i][j+1]!=WHITE)used++;

		if(light_num > _map[i][j])return false;
		if(light_num+used==_map[i][j]&&used>0)return false;

		return true;
	}

	bool isDone(vector<vector<int> > &_map)
	{
		bool flag=true;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				/* code */
				if(_map[i][j]==WHITE||_map[i][j]==FORBIDDENED)
					flag=false;
			}
		}
		flag=flag&&check(_map);
		return flag;
	}
	void newLine(vector<int>&line)
	{
		line.resize(col);
		for (int i = 0; i < line.size(); ++i)
		{
			/* code */
			line[i]=BLACK;
		}
	}
	void Ndebug(vector<vector <int> >&_map)
	{
		for (int i = 1; i < row-1; ++i)
		{
			for (int j = 1; j < col-1; ++j)
			{
				/* code */
				if(_map[i][j]==LIGHT)
					cout<<1<<" ";
				else
					cout<<0<<" ";

			}
			cout<<endl;
		}
		cout<<endl;
	}
	void print(vector<vector<int> >&_map)
	{
		for (int i = 1; i < row-1; ++i)
		{
			for (int j = 1; j < col-1; ++j)
			{
				/* code */
				cout<<_map[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	void copy(vector<vector<int> >&_map)
	{
		_map.resize(row);
		for (int i = 0; i < row; ++i)
		{
			_map[i].resize(col);
			for (int j = 0; j < col; ++j)
			{
				/* code */
				_map[i][j]=map[i][j];
			}
		}
	}
	void copy(vector<vector<int> >& dest_map,vector<vector<int> >& source_map)
	{
		dest_map.resize(row);
		for (int i = 0; i < row; ++i)
		{
			dest_map[i].resize(col);
			for (int j = 0; j < col; ++j)
			{
				/* code */
				dest_map[i][j]=source_map[i][j];
			}
		}
	}
	void wirte(vector<vector<int> >&_map)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				/* code */
				map[i][j]=_map[i][j];
			}
		}
	}
};
