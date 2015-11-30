#pragma once

#include "2-3-4TreeNode.h"
#include "../global.h"

template <typename keyType>
class Tree234
{
	typedef tree234Node<keyType> node;
public:
	Tree234()
	{
		root=NULL;
	}
	~Tree234()
	{
		deconstruct(root);
	}
	void inorderTraversal()
	{
		_inorderTraversal(root);
	}
	void debugTraversal()
	{
		_debugTraversal(root);
	}
	void search(keyType key)
	{
		if(_search(root,key))
			cout<<"key"<<key<<"查找成功";
		else
			cout<<"key"<<key<<"查找失败";
	}
	void insert(keyType key)
	{
		_insert(root,key);
	}
private:
	node *root;

	void deconstruct(node *cur)
	{
		if(!cur)return;
		for (unsigned i=0;i<cur->pVector.size();i++)
			if(cur->pVector[i])
				deconstruct(cur->pVector[i]);
		delete cur;
		cur=NULL;
	}
	void _inorderTraversal(node *cur)
	{
		if(!cur)return ;
		if(cur->pVector[0])
			_inorderTraversal(cur->pVector[0]);
		for (unsigned i=0;i<cur->keyVector.size();i++)
		{
			cout<<cur->keyVector[i]<<" ";
			if(cur->pVector[i+1])
				_inorderTraversal(cur->pVector[i+1]);
		}
	}
	void _debugTraversal(node *cur)
	{
		if(!cur)return ;
		cur->print();
		for (unsigned i=0;i<cur->pVector.size();i++)
		{
			if(cur->pVector[i])
				_debugTraversal(cur->pVector[i]);
		}
	}
	bool _search(node*cur,keyType key)
	{
		bool isFound=false;
		unsigned i=0;
		if(!cur)return isFound;
		for (i=0;i<cur->keyVector.size();i++)
		{
			if(key==cur->keyVector[i])
			{
				isFound=true;
				return isFound;
			}
			if(key<cur->keyVector[i])
			{
				if(cur->pVector[i])
				{
					isFound|=_search(cur->pVector[i],key);
					return isFound;
				}
			}
		}
		return _search(cur->pVector[i],key);
	}
	void _insertNode(node *&cur,keyType key)
	{
			unsigned i=0;
			for (i=0;i<cur->keyVector.size();i++)
			{
				if(key==cur->keyVector[i])
					return;
				if(key<cur->keyVector[i])
				{
					if(cur->pVector[i])
						_insert(cur->pVector[i],key);
				}
			}
			_insert(cur->pVector[i],key);
	}
	void _insert(node *&cur,keyType key)
	{
		if(!cur)return ;
		if(cur->nodeType()==4)
		{
			split(cur);
			/**
			 * 此时cur指原节点的父节点
			 */
			 _insertNode(cur,key);
		}
		else if(!cur->isLeafNode())
			_insertNode(cur, key);
		else if(cur->isLeafNode())
			cur->merge(cur,key);
	}
	void split(node * &cur)
	{
		if(!cur)return;
		node *tmp=cur;
		/**
		 * 指针操作	4node
		 */
		node *node1=new node(2);
		node *node2=new node(2);
		node *node3=new node(2);
		node1->keyVector[0]=tmp->keyVector[1];
		node1->pVector[0]=node2;
		node1->pVector[1]=node3;
		node2->keyVector[0]=tmp->keyVector[0];
		node2->pVector[0]=tmp->pVector[0];
		node2->pVector[1]=tmp->pVector[1];
		node3->keyVector[0]=tmp->keyVector[2];
		node3->pVector[0]=tmp->pVector[2];
		node3->pVector[1]=tmp->pVector[3];
		cur=node1;
		node1=node2=node3=NULL;


		cur=cur->merge(tmp->parent);
		delete tmp;
	}

};