#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<vector>
#include<queue>

//���������Ľڵ�
template<class T>
class HuffmanTreeNode
{
public:
	HuffmanTreeNode(const T & w=T())
		:_pleft(nullptr)
		, _pright(nullptr)
		, _pparent(nullptr)
		, _weight(w)
	{}

	HuffmanTreeNode<T> * _pleft;
	HuffmanTreeNode<T> * _pright;
	HuffmanTreeNode<T> * _pparent;
	T _weight;
};

template<class T>
class Great
{
	typedef HuffmanTreeNode<T> Node;
public:
	bool operator ()(const Node *left, const Node *right){
		return left->_weight > right->_weight;
	}
};

template<class T>
class HuffmanTree
{
	//���ڹ��������Ľڵ�ʹ��Ƶ�ʸ����Զ���������
	typedef HuffmanTreeNode<T> Node;
public:
	//����һ�ÿ���
	HuffmanTree()
	:_proot(nullptr){}
	//�����������
	HuffmanTree(const std::vector<T>& v,const T & inval){
		CreatHuffmanTree(v,inval);//inval��ʾ��ЧȨֵ���������ڹ����������ʱ�����0��
	}

	~HuffmanTree(){
		DestroyHuffmanTree(_proot);
	}

	//������������
	void CreatHuffmanTree(const std::vector<T> v , const T & inval=T()){
		//1.�Ѳ����������Ϣ�ŵ����ȼ������н��й���
		//���ȼ�����Ĭ�Ϲ���Ķ��Ǵ�ѣ�����Ҫ�ṩС�ѵĹ��췽ʽ
		std::priority_queue<Node*,std::vector<Node *>,Great<T>> q;
		for (auto e : v){
			//��ֵΪ0��ʱ��Ͳ�Ҫ�������зţ�����������������Ҷ�ӽڵ����Һ��Ӳ�Ϊ�գ�
			if (e == inval){
				continue;
			}
			q.push(new Node(e));
		}
		//2.�����������
		while (q.size() > 1){
			Node * pleft = q.top();
			q.pop();
			Node * pright = q.top();
			q.pop();
			Node * tmp = new Node(pleft->_weight + pright->_weight);
			tmp->_pleft = pleft;
			tmp->_pright = pright;
			pleft->_pparent = tmp;
			pright->_pparent = tmp;
			q.push(tmp);
		}
		_proot = q.top();
	}

	Node* GetRoot(){
		return _proot;
	}
private:
	void DestroyHuffmanTree(Node *&root){
		if (root){
			//ͨ����������ķ�ʽ����һ�Ŷ�����
			DestroyHuffmanTree(root->_pleft);
			DestroyHuffmanTree(root->_pright);
			delete root;
			root = nullptr;
		}
	}
private:
	Node * _proot;
};
