#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<queue>
using namespace std;
#include<vector>
#include<functional>
#include<stdlib.h>
#include<algorithm>

template<class T>
class HaFuManTreeNode//�������������Ľڵ�ṹ
{
public:
	    HaFuManTreeNode(const T & w=T())
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, weight(w)
	    {
		}


public:
	HaFuManTreeNode * _pLeft;
	HaFuManTreeNode * _pRight;
	HaFuManTreeNode * _pParent;
	T weight;
};

template<class T>
class Com
	//�Ƚ��������ȼ�����
{
public:
	//typedef HaFuManTreeNode<int> Node;
	bool operator ()( const T & Left, const T & Right)
	{
		if (Left->weight._count>Right->weight._count)//Ĭ�ϴ�ѣ�С�ںţ����ĳ�С�ѣ����ںţ�
		{
			return  true;
		}
		else{
			return false;
		}
	}
};


template<class T>
class HaFuManTree
{
	typedef HaFuManTreeNode<T> Node;
public:
	HaFuManTree(vector<T> & v)
		:_pRoot(new Node)
	{
		priority_queue<Node *,vector<Node *>,Com<Node *>> q;
		//1.���ȴ������нڵ㲢�������ɭ���У����ȼ����й���
		for (int i = 0; i < v.size(); ++i)
		{
			if (v[i]._count != 0)
			{
				Node * cur = CreatHaFuManTree(v[i]);
				q.push(cur);
			}
			
		}
		//2.����Щ�ڵ㹹��Ϊһ�ù�������
		//Node * tmp = new Node;
		//ע�⣺������������д��������ôtmpָ���ǹ̶��ģ�ÿһ���޸�ʱ�������ЧӦ
#if	1
		while (q.size()>1)
		{
			//Ϊtmpָ�����·������ڴ�ռ�
			Node * tmp = new Node;//���������д������ÿһ�ν�������Ϊtmp���¿��ٿռ䣬�޸���ʱҲ����Ӱ����
			Node *Left = q.top();
			q.pop();
			Node *Right = q.top();
			q.pop();
			tmp->_pLeft = Left;
			tmp->_pRight = Right;
			tmp->weight._count = Left->weight._count+ Right->weight._count;
			Left->_pParent = tmp;
			Right->_pParent = tmp;
			q.push(tmp);
		}

		
#endif
		_pRoot = q.top();
		/////////////////////////////////////
		//3.��ȡ����������
		GetHaFuManCode(_pRoot,v);//�ѽ���ȷ�ı��뱣�浽����
		
	}


	~HaFuManTree()
	{
		Destroy(_pRoot);
	}

	Node * CreatHaFuManTree(const T & t = T())
	{
		Node * cur = new Node(t);
		return cur;
	}
public:


	void GetHaFuManCode(Node * root, vector<T> & v)//�涨����Ϊ0������Ϊ1
	{
		//�����еı�����Ϣ���������������Ǳ���Ҫ���ò������յı���
		if ((root) == nullptr){
			return;
		}
		if (root->_pLeft == nullptr&&root->_pRight == nullptr){
			Node *cur = root;
			Node *res = cur;
			while (cur != _pRoot){
				if ((cur) == (cur)->_pParent->_pLeft){//cur������
					(res)->weight._strcode += '0';
				}
				else if ((cur) == (cur)->_pParent->_pRight){
					(res)->weight._strcode += '1';
				}
				cur = (cur)->_pParent;
			}
			reverse(res->weight._strcode.begin(), res->weight._strcode.end());
			for (int i = 0; i < v.size(); ++i){
				if (v[i]._ch == res->weight._ch){
					v[i]._strcode = res->weight._strcode;
				}
			}
		}

		GetHaFuManCode(root->_pLeft,v);
		GetHaFuManCode(root->_pRight,v);
	}



	Node * GetRoot()
	{
		return _pRoot;
	}
private:
	void Destroy(Node *& _proot)
	{
		delete _proot;
	}
	Node *_pRoot;
};


