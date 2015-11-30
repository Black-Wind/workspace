#pragma once

#include "../global.h"

#define RED true;
#define BLACK false;

template <class keyType>
class LLRBTreeNode
{
typedef LLRBTreeNode node;
public:
	LLRBTreeNode(keyType _key)
	{
		left=NULL;
		right=NULL;
		color=true;
		key=_key;
	}

	~LLRBTreeNode()
	{
		left=NULL;
		right=NULL;
	}
	/**
	 * 自定义的key比较函数
	 * @param  	_key
	 * @return	0代表相同;>0代表节点的key大于_key;<0代表节点的key小于_key
	 */
	int compare(keyType _key)
	{
		if(key==_key)return 0;
		if(key<_key)return -1;
		if(key>_key)return 1;
	}
	keyType key;
	node *left;
	node *right;
	bool color;
};

template <class keyType>
class LLRBTree
{

	typedef LLRBTreeNode<keyType>node;
public:
	LLRBTree()
	{
		root=NULL;
	}

	~LLRBTree()
	{
		deconstruct(root);
	}
	void search(keyType key)
	{
		if(_search(root,key))
			cout<<"key"<<key<<"查找成功"<<endl;
		else
			cout<<"key"<<key<<"查找失败"<<endl;
	}
	void insert(keyType key)
	{
		_insert(root,key);
		//注意根的颜色修改
		root->color=BLACK;
	}
	void orderTraversal()
	{
		_orderTraversal(root);
		cout<<endl;
	}
	void printPreTraversal()
	{
		cout<<"PreTraversal: ";
		_printPreTraversal(root);
		cout<<endl;
	}
	void printPostTraversal()
	{
		cout<<"PostTraversal: ";
		_printPostTraversal(root);
		cout<<endl;
	}
	void remove(keyType key)
	{
		_remove(root,key);
		//注意根的颜色修改
		root->color=BLACK;
	}
	void setOutput(bool tmp)
	{
		isOutput=tmp;
	}
private:

	node *root;
	bool isOutput;
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
	bool _search( node *&cur,keyType key)
	{
		bool isFound=false;
		if(!cur)return isFound;
		int result=cur->compare(key);
		if(result==0)
			isFound=true;
		else if(result>0)
			isFound=_search(cur->left,key);
		else
			isFound=_search(cur->right,key);
		return isFound;
	}
	void _orderTraversal(node* &cur)
	{
		if(!cur)return;
		_orderTraversal(cur->left);
		if(isOutput)
			cout<<cur->key<<" ";
		_orderTraversal(cur->right);
	}
	/**
	 * 模仿前序遍历
	 */
	void _printPreTraversal( node* &cur)
	{
		if(!cur)return;
		if(isRedNode(cur))
		{
			_printPreTraversal(cur->left);
			_printPreTraversal(cur->right);
		}
		else
		{
			if(isRedNode(cur->left)&&isRedNode(cur->right))
			{
				if(isOutput)
					cout<<"["<<cur->left->key<<","<<cur->key<<","<<cur->right->key<<"] ";
			}
			else if(isRedNode(cur->left)&&!isRedNode(cur->right))
			{
				if(isOutput)
					cout<<"["<<cur->left->key<<","<<cur->key<<"] ";
			}
			else
			{
				if(isOutput)
					cout<<cur->key<<" ";
			}
			_printPreTraversal(cur->left);
			_printPreTraversal(cur->right);
		}

	}
	/**
	 * 模仿前序遍历
	 */
	void _printPostTraversal( node* &cur)
	{
		if(!cur)return;
		if(isRedNode(cur))
		{
			_printPostTraversal(cur->left);
			_printPostTraversal(cur->right);
		}
		else
		{
			_printPostTraversal(cur->left);
			_printPostTraversal(cur->right);
			if(isRedNode(cur->left)&&isRedNode(cur->right))
			{
				if(isOutput)
					cout<<"["<<cur->left->key<<","<<cur->key<<","<<cur->right->key<<"] ";
			}
			else if(isRedNode(cur->left)&&!isRedNode(cur->right))
			{
				if(isOutput)
					cout<<"["<<cur->left->key<<","<<cur->key<<"] ";
			}
			else
			{
				if(isOutput)
					cout<<cur->key<<" ";
			}

		}

	}
	bool isRedNode(node* &cur)
	{
		if(!cur)return false;
		return cur->color==RED;
	}
	void _insert(node*&cur,keyType key)
	{
		if(!cur)
		{
			cur=new node(key);
			return ;
		}
		if(isRedNode(cur->left)&&isRedNode(cur->right))
			flipColor(cur);
		int result=cur->compare(key);
		if(result==0)
		{

		}
		else if(result>0)
			_insert(cur->left,key);
		else if(result<0)
			_insert(cur->right,key);

		if(!isRedNode(cur->left)&&isRedNode(cur->right))
			leftRotate(cur);
		if(isRedNode(cur->left)&&isRedNode(cur->left->left))
			rightRotate(cur);
	}
	void flipColor( node *&cur)
	{
		if(!cur)return ;
		if(cur->left)
			cur->left->color=!cur->left->color;
		if(cur->right)
			cur->right->color=!cur->right->color;
		cur->color=!cur->color;
	}
	void  leftRotate(node * &cur)
	{

		node *tmp=cur->right;
		cur->right=tmp->left;
		tmp->left=cur;
		cur=tmp;

		cur->color=cur->left->color;
		cur->left->color=RED;
	}
	void rightRotate(node *&cur)
	{

		node *tmp=cur->left;
 		cur->left=tmp->right;
		tmp->right=cur;
		cur=tmp;

		cur->color=cur->right->color;
		cur->right->color=RED;
	}
	void _remove(node*&cur,keyType key)
	{
		if(!cur)return;
		if(cur->compare(key)>0)
		{
			if(cur->left&&!isRedNode(cur->left)&&!isRedNode(cur->left->left))
			{
				moveRedLeft(cur);
			}
			_remove(cur->left,key);
		}
		else
		{
			if(isRedNode(cur->left))
				rightRotate(cur);
			// cout<<0<<" "<<cur->key<<endl;
			if(cur->compare(key)==0&&!cur->right)
			{
				delete cur;
				cur=NULL;
				return;

			}
			// cout<<1<<" "<<cur->key<<endl;
			if(cur->right&&!isRedNode(cur->right)&&!isRedNode(cur->right->left))
				moveRedRight(cur);
			// cout<<2<<" "<<cur->key<<endl;
			if(cur->compare(key)==0)
			{
				cur->key=removeMin(cur->right);
				// cout<<3<<" "<<cur->key<<endl;
			}

			else _remove(cur->right,key);
		}
		repair(cur);
	}
	void  repair(node*&cur)
	{
		if(!cur)return;
		if(isRedNode(cur->right))
			leftRotate(cur);
		if(cur->left&&isRedNode(cur->left)&&isRedNode(cur->left->left))
			rightRotate(cur);
		if(isRedNode(cur->left)&&isRedNode(cur->right))
			flipColor(cur);
	}
	void moveRedLeft(node*&cur)
	{
		if(!cur)return;
			flipColor(cur);
		if(cur->right&&isRedNode(cur->right->left))
		{
			rightRotate(cur->right);
			leftRotate(cur);
			flipColor(cur);
		}
		repair(cur->right);
	}
	void moveRedRight(node*&cur)
	{
		if(!cur)return;
			flipColor(cur);
		if(cur->left&&isRedNode(cur->left->left))
		{
			rightRotate(cur);
			flipColor(cur);
		}
		repair(cur->left);
	}
	keyType  removeMin(node*&cur)
	{
		keyType key;
		if(!cur)return key;
		if(!cur->left)
		{
			key=cur->key;
			delete cur;
			cur=NULL;
			return key;
		}
		if(cur->left&&!isRedNode(cur->left)&&!isRedNode(cur->left->left))
			moveRedLeft(cur);
		key=removeMin(cur->left);
		repair(cur);
		return key;
	}

};
