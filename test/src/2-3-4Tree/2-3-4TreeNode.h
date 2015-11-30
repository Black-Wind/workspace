#pragma once

#include "../global.h"

template <class keyType>
class tree234Node
{
public:
	tree234Node(int _nodeType)
	{
		parent=NULL;
		isFirstAskForLeaf=true;
		_isLeafNode=true;
		this->pVector.resize(_nodeType);
		this->keyVector.resize(_nodeType-1);
	}
	~tree234Node()
	{
		parent=NULL;
		keyVector.clear();
		for(unsigned i=0;i<this->pVector.size();i++)
			this->pVector[i]=NULL;
		pVector.clear();
	}
	int nodeType()
	{
		return pVector.size();
	}
	bool isLeafNode()
	{
		if(isFirstAskForLeaf)
		{
			for(unsigned i=0;i<pVector.size();i++)
				_isLeafNode &=(pVector[i]==NULL);
			isFirstAskForLeaf=false;
		}
		else return _isLeafNode;
	}
	void print()
	{
		cout<<"[";
		for(unsigned i=0;i<keyVector.size();i++)
		{
				cout<<keyVector[i];
				if(i!=keyVector[i].size()-1)
					cout<<",";
		}
		cout<<"] ";
	}
	void merge(tree234Node*& cur,keyType key)
	{
		if(nodeType()==4)
		{
			cout<<nodeType()<<"node key-merge error"<<endl;
		}
		else if(nodeType()==3)
		{
			keyVector.push_back(key);
			sort(keyVector.begin(),keyVector.end());
			pVector.resize(4);
		}
		else if(nodeType()==2)
		{
			keyVector.push_back(key);
			sort(keyVector.begin(),keyVector.end());
			pVector.resize(3);
		}
		else
		{
			cout<<nodeType()<<"node key-merge error"<<endl;
		}
	}
	void merge(tree234Node*& cur,tree234Node*& node)
	{
		if(nodeType()==4)
		{
			cout<<nodeType()<<"node node-merge error"<<endl;
		}
		else if(nodeType()==3)
		{
			cout<<nodeType()<<"node node-merge error"<<endl;
		}
		else if(nodeType()==2)
		{

		}
		else
		{
			cout<<nodeType()<<"node node-merge error"<<endl;
		}
	}
	tree234Node *parent;
	std::vector<tree234Node*> pVector;
	std::vector<keyType>	keyVector;
private:
	bool isFirstAskForLeaf;
	bool _isLeafNode;
};





