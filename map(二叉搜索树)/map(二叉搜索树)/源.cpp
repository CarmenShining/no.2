#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

template<class T>
struct BSTNode//�����������Ľڵ����
{	
	BSTNode(const T & data = T())
	:_pLeft(nullptr)
	, _pRight(nullptr)
	, _data(data)
	{}

	BSTNode<T> * _pLeft;
	BSTNode<T> * _pRight;
	T _data;
};

template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
public:
	BSTree()
		:_pRoot(nullptr)
	{}

	//�������������
	bool Insert(const T & data)
	{
		//�����Ϊ�գ�newһ���ڵ㲢��ֵ����
		if (_pRoot == nullptr){
			_pRoot = new BSTNode<T>;
			_pRoot->_data = data;
			return true;
		}
		//�������Ϊ��˵���Ѿ���Ԫ�أ��Ƚ�Ҫ�����Ԫ�غ�ÿ���ڵ�Ĵ�С������
		Node *cur = _pRoot;
		Node *parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_data > data){
				//����ֵ�Ƚϴ�����Ҫ�����ֵҪ����������
				cur = cur->_pLeft;
			}
			else if (cur->_data < data){
				//����ֵ�Ƚ�С��������������
				cur = cur->_pRight;
			}
			else{
				return false;
			}
		}
		//����Ԫ��
		cur = new Node(data);
		if (parent->_data > data){
			parent->_pLeft = cur;
		}
		else{
			parent->_pRight = cur;
		}
		return true;
	}

	/////////////////////////////////////////////////////////////////////////

	Node *Find(const T& data)
	{
		Node *cur = _pRoot;
		while (cur)
		{
			if (cur->_data == data){
				return cur;
			}
			if (cur->_data>data)
			{
				//Ҫ�ҵıȸ��ڵ�С��˵����������
				cur = cur->_pLeft;
			}
			else{
				//Ҫ�ҵıȸ��ڵ��˵����������
				cur = cur->_pRight;
			}
		}
		return nullptr;
	}

	/////////////////////////////////////////////////
	//ɾ��
	bool Delete(const T & data)
	{
		if (nullptr == _pRoot){
			return false;
		}
		//��Ҫɾ���Ľڵ��λ��
		Node * pCur = _pRoot;//Cur����Ҫɾ���Ľڵ�
		Node * pParent = nullptr;//pParent����Cur��˫�ף����û������ڵ���޷���ɾ����Ľڵ㽨����ϵ
		while (pCur)
		{
			if (data == pCur->_data){
				break;
			}
			else if (data < pCur->_data){
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else{
				pParent = pcur;
				pCur = pCur->_pRight;
			}
		}

		if (nullptr == pCur){
			return false;
		}
		//ɾ��
		Node *pDelNode = pCur;
		//ɾ�������������
		//Ҫɾ���Ľڵ���Ҷ�ӽڵ㡢Ҫɾ���Ľڵ�ֻ���Һ��ӽڵ㡢Ҫɾ���Ľڵ�ֻ�����ӽڵ㡢Ҫɾ���Ľڵ������Һ��ӽڵ�
		//��Ҷ�ӽڵ��ֻ���Һ��ӽڵ���Ե���һ�����������

		if (nullptr == pCur->_pLeft){
			//1.����Ϊ��
			if (nullptr == pParent){
				//2.pCur�Ǹ��ڵ�
				_pRoot = pCur->_pRight;
			}
			else{
				if (pCur == pParent->_pLeft){//���Ҫɾ�����ǽڵ���pParent����ߣ��ͽ�pParent�������֮����
					pParent->_pLeft = pCur->_pRight;
				}
				else{
					pParent->_pRight = pCur->_pRight;
				}
			}
		}
		else if (nullptr == pCur->_pRight){
			//3.�Һ���Ϊ��
			if (nullptr == pParent){
				_pRoot = pCur->_pLeft;
			}
			else{
				if (pCur == pParent->_pLeft){
					pParent->_pLeft = pCur->_pLeft;
				}
				else{
					pParent->_pRight = pCur->_pLeft;
				}
			}
		}
		else{
			//4.���Һ��Ӿ�����
			//˼·�������ڴ�ɾ���Ľڵ��������������������һ����ڵ�
			//����������������С�Ľڵ���������������Ľڵ㣨��Ϊ�滻����Ҫ���ֶ��������������ԣ�
			//���·�����������������С�Ľڵ�
			Node * pDel = pCur->_pRight;//Del������ڵ�
			pParent = pCur;
			while (pDel->_pLeft){
				pParent = pDel;
				pDel = pDel->_pLeft;
			}
			pCur->_data = pDel->_data;//��������
			if (pParent->_pLeft == pDel){
				pParent->_pLeft = pDel->_pRight;
			}
			else{
				pParent->_pRight = pDel->_pRight;
			}
			pDelNode = pDel;
		}
		delete pDelNode;
		return true;
	}


	/////////////////////////////////////////////////////////
	//�ҵ������Ľڵ�
	Node*LeftMost()
	{
		if (_pRoot == nullptr){
			return nullptr;
		}
		Node*cur = _pRoot;
		while (cur->_pLeft){
			cur = cur->_pLeft;
		}
		return cur;
	}

	//�ҵ����Ҳ�Ľڵ�
	Node * RightMost()
	{
		if (nullptr == _pRoot){
			return nullptr;
		}
		Node * cur = _pRoot;
		while (cur->_pRight){
			cur = cur->_pRight;
		}
		return cur;
	}


	//�����������������
	void Display()//��Ϊ���ⲿ�޷��õ����ڵ�����Ҫ�ٷ�װһ��
	{
		DisPlay(_pRoot);
	}

private:
	void DisPlay(Node *root)
	{
		if (root){
			DisPlay(root->_pLeft);
			cout << root->_data << " ";
			DisPlay(root->_pRight);
		}
	}
	Node * _pRoot;
};

void TestFun()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> node;
	for (auto & e : a){
		node.Insert(e);
	}
	//node.Display();
	cout << node.Find(5) << endl;
}

int main()

{

	TestFun();
	system("pause");
	return 0;
}