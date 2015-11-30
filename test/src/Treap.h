#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


template<class keyType>
class Item
{
public:
 Item(){}
 Item(keyType _key,string _s1,string _s2,string _s3,\
 	string _s4):key(_key),s1(_s1),s2(_s2),s3(_s3),s4(_s4){}
 void print()
 {
 	cout<<key<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4;
 }

 keyType key;
 string s1,s2,s3,s4;
};

template <class keyType>
class TreapNode{
public:
	typedef Item<keyType> _Item;

	TreapNode(){
		prior=rand();
		left=NULL;
		right=NULL;
		leftDesNum=0;
		rightDesNum=0;
		// cout<<"节点prior:"<<prior<<endl;
	}
	TreapNode(_Item item)
	{
		key=item.key;
		prior=rand();
		left=NULL;
		right=NULL;
		leftDesNum=0;
		rightDesNum=0;
		// cout<<"节点prior:"<<prior<<endl;
		items.push_back(item);
	}
	~TreapNode()
	{
		// cout<<"正在析构此节点"<<endl;
		items.clear();
		left=NULL;
		right=NULL;
	}
	int nodeNum()
	{
		return leftDesNum+rightDesNum+1;
	}
	void print()
	{
		cout<<key<<" "<<prior<<" "<<" 左子树后代的数量:"<<leftDesNum<<" 右子树后代的数量:"<<rightDesNum<<" "<<endl;
		for(unsigned int i=0;i<items.size();i++)
		{
			items[i].print();
 			cout<<endl;
		}
	}

	TreapNode *left;
	TreapNode *right;
	keyType key;
	long int prior;
	int leftDesNum; 	//左子树后代的数量
	int rightDesNum;	//右子树后代的数量
	std::vector<_Item > items;
};



template <class keyType>
class Treap{
public:
	typedef TreapNode<keyType> node;
	typedef Item<keyType> _Item;

	Treap(){
		srand((unsigned)time(NULL));
		root=NULL;
	}
	~Treap(){
		deconstruct(root);
	}
	void insert(const _Item * pItem)
	{
		insert(*pItem);
	}
	void insert(const _Item & item){
		if(!root){
			root =new node (item);
			return ;
		}
		insert(root,item);
	}
	void batchInsert();
	void searchByKey(const _Item &item)
	{
		bool isEx=search(root,item.key);
		// if(!isEx)cout<<"key值为"<<item.key<<"的数据不存在"<<endl;
	}
	void singleKeyRemove(const _Item &item)
	{
		// cout<<"root:"<<root->key<<endl;
		remove(root,item.key);
		// if(remove(root,item.key))
		// 	cout<<"没有找到key值为"<<item.key<<"的数据"<<endl;
	} //注意set root=null
	void intervalKeyRemove(int start,int end)
	{
		_intervalKeyRemove(root,start,end);
	}
	void kthRemove(int kth)
	{
		_kthReomve(root,kth);
	}
	void intervalKthRemove(int ath,int bth)
	{
		_intervalKthRemove(root,ath,bth);
	}
	void print(){
		printKeyPre(root);
	}
private:
	node *root;

	void deconstruct(node *cur)
	{
		if(!cur)return;
		if(cur->left)
			deconstruct(cur->left);
		if(cur->right)
			deconstruct(cur->right);

		delete cur;
		cur=NULL;
	}
	void printKeyPre(node *cur)		//前序遍历
	{
		if(!cur){
			cout<<"空树"<<endl;
			return;
		}
		cur->print();
		if(cur->left)
			printKeyPre(cur->left);
		if(cur->right)
			printKeyPre(cur->right);
	}
	//前提cur非空
	void  leftRotate(node * &cur)
	{

		node *tmp=cur->right;

		cur->right=tmp->left;

		if(!cur->right)
			cur->rightDesNum=0;
		else if(cur->right)
 			cur->rightDesNum=cur->right->nodeNum();

		tmp->left=cur;

		if(!tmp->left)
			tmp->leftDesNum=0;
		if(tmp->left)
			tmp->leftDesNum=tmp->left->nodeNum();

		cur=tmp;

	}
	//前提cur非空
	void rightRotate(node *&cur)
	{



		node *tmp=cur->left;

 		cur->left=tmp->right;

		if(!cur->left)
			cur->leftDesNum=0;
		else if(cur->left)
 			cur->leftDesNum=cur->left->nodeNum();

		tmp->right=cur;

		if(!tmp->right)
			tmp->rightDesNum=0;
		if(tmp->right)
			tmp->rightDesNum=tmp->right->nodeNum();


		cur=tmp;
	}
	//前提cur非空
	bool insert(node *&cur,const _Item & item)
	{
		bool isInserted=false;
	    if (item.key<cur->key)
		{
			if(!(cur->left))
			{
				cur->left=new node(item);
				isInserted=true;
			}
			else
				isInserted=insert(cur->left,item);
			if(isInserted)
				cur->leftDesNum++;
			if(cur->left->prior<cur->prior)
				rightRotate(cur);


		}
		else if(item.key>cur->key)
		{
			if(!(cur->right))
			{
				cur->right=new node(item);
				isInserted=true;
			}
			else
				isInserted=insert(cur->right,item);
			if(isInserted)
				cur->rightDesNum++;
			if(cur->right->prior<cur->prior)
				leftRotate(cur);

		}
		else if (item.key==cur->key)
		{

			cur->items.push_back(item);

		}
		return isInserted;
	}

	bool search(node *& cur,keyType key)
	{
		bool isEx=false;
		if(!cur)return isEx;
		if(cur->key==key)
		{
			// cout<<"search成功"<<endl;
			// cur->print();
			// cout<<"key为"<<key<<"的数据排名第"<<cur->rightDesNum+1<<"位"<<endl;
			isEx=true;
		}
		else if(cur->key<key)
			isEx=search(cur->right,key);
		else
			isEx=search(cur->left,key);
		return isEx;
	}
	bool remove(node *& cur,keyType key)
	{
		bool isRemoved=false;
		if(!cur)return isRemoved;
		if(cur->key==key)
		{
			if(!cur->left||!cur->right)
			{
				node *tmp=cur;
				if(!cur->right)
				{

					cur=cur->left;
				}
				else
				{

					cur=cur->right;
				}

				delete tmp;
			}
			else
			{
				if(cur->left->prior<cur->right->prior)
				{
					rightRotate(cur);
					if(cur->rightDesNum>0)
						cur->rightDesNum--;
					remove(cur->right,key);

				}
				else
				{
					leftRotate(cur);
					if(cur->leftDesNum>0)
						cur->leftDesNum--;
					remove(cur->left,key);

				}
			}
			isRemoved=true;
		}
		else if(key<cur->key)
		{
			isRemoved=remove(cur->left,key);
			if(isRemoved)
				cur->leftDesNum--;
		}
		else if(key>cur->key)
		{
			isRemoved=remove(cur->right,key);
			if(isRemoved)
				cur->rightDesNum--;
		}
		return isRemoved;
	}
	int _intervalKeyRemove(node * &cur,int start,int end)
	{
		int numLeftRemoved=0,numRightRemoved=0,isCurRemoved=0;
		if(!cur)return 0;
		if(end<start)return 0;
		if(cur->key<start)
			numRightRemoved+=_intervalKeyRemove(cur->right,start,end);
		else if(cur->key>end)
			numLeftRemoved+=_intervalKeyRemove(cur->left,start,end);
		else if(cur->key==start)
		{
			numRightRemoved+=_intervalKeyRemove(cur->right,start+1,end);

			isCurRemoved=1;
		}
		else if(cur->key==end)
		{
			numRightRemoved+=_intervalKeyRemove(cur->left,start,end-1);

			isCurRemoved=1;
		}
		else if(cur->key>start&&cur->key<end)
		{
			numRightRemoved+=_intervalKeyRemove(cur->left,start,cur->key-1);
			numRightRemoved+=_intervalKeyRemove(cur->right,cur->key+1,end);

			isCurRemoved=1;
		}
		cur->leftDesNum-=numLeftRemoved;
		cur->rightDesNum-=numRightRemoved;
		if(isCurRemoved)remove(cur,cur->key);
		return isCurRemoved+numLeftRemoved+numRightRemoved;
	}
	bool _kthReomve(node * &cur,int kth)
	{
		bool isRemoved=false;
		if(!cur)return isRemoved;

		int curTh=cur->rightDesNum+1;
		if(curTh==kth)
		{
			remove(cur,cur->key);
			isRemoved=true;
		}
		else if(curTh>kth)
		{
			isRemoved=_kthReomve(cur->right,kth);
			if(isRemoved)cur->rightDesNum--;
		}
		else if(curTh<kth)
		{
			isRemoved=_kthReomve(cur->left,kth-curTh);
			if(isRemoved)cur->leftDesNum--;
		}
		return isRemoved;
	}

	int _intervalKthRemove(node * &cur,int ath,int bth)
	{

		int numLeftRemoved=0,numRightRemoved=0,isCurRemoved=0;
		if(!cur)return 0;
		if(ath>bth)return 0;
		int curTh=cur->rightDesNum+1;
		if(curTh<ath)
			numLeftRemoved+=_intervalKthRemove(cur->left,ath-curTh,bth-curTh);
		else if(curTh>bth)
			numRightRemoved+=_intervalKthRemove(cur->right,ath,bth);
		else if(curTh==ath)
		{
			numLeftRemoved+=_intervalKthRemove(cur->left,1,bth-curTh);

			isCurRemoved=1;
		}
		else if(curTh==bth)
		{
			numRightRemoved+=_intervalKthRemove(cur->right,ath,bth-1);

			isCurRemoved=1;
		}
		else if(curTh>ath&&curTh<bth)
		{
			numLeftRemoved+=_intervalKthRemove(cur->left,1,bth-curTh);
			numRightRemoved+=_intervalKthRemove(cur->right,ath,curTh-1);

			isCurRemoved=1;

		}
	cur->leftDesNum-=numLeftRemoved;
	cur->rightDesNum-=numRightRemoved;
	if(isCurRemoved)remove(cur,cur->key);
	return isCurRemoved+numLeftRemoved+numRightRemoved;
	}
};


