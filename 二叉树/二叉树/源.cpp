#define _CRT_SECURE_NO_WARNINGS 1
#define NULL 0
#include<iostream>
using namespace std;
#include<string.h>
#include<stack>
#include<cstdio>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#if 0

typedef char datatype;
typedef struct node{
	datatype elem;
	struct node * lchild, *rchild;
}BTNode, *BinTree;


//BinTree createBinTree_1(Binn)

BinTree CreateBTree_2()//����������
{
	BinTree bt = NULL;
	char ch;
	scanf("%c", &ch);
	if (ch != '#'){
		bt = new	BTNode;
		bt->elem = ch;
		bt->lchild = CreateBTree_2();
		bt->rchild = CreateBTree_2();
	}
	return bt;
}

void preOrder(BinTree root)
{
	if (root != NULL){
		cout << root->elem << " ";
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
	//cout<<endl;
}

void inOrder(BinTree root)
{
	if (root != NULL){
		inOrder(root->lchild);
		cout << root->elem << " ";
		inOrder(root->rchild);
	}
	//cout<<endl;
}

void postOrder(BinTree root)
{
	if (root != NULL){
		postOrder(root->lchild);
		postOrder(root->rchild);
		cout << root->elem << " ";
	}
	//cout<<endl;
}

int maxDepth(BinTree root)
{
	int m, n;
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		m = maxDepth(root->lchild);
		n = maxDepth(root->rchild);
		if (m>n){
			return (m + 1);
		}
		else
		{
			return (n + 1);
		}
	}

}



void display(BinTree root)//չʾ������
{
	if (root != NULL){
		cout << root->elem;
		if (root->lchild != NULL || root->rchild != NULL){
			cout << '(';
			display(root->lchild);
		}
		if (root->rchild != NULL){
			cout << ',';
			display(root->rchild);
			cout << ')';
		}
	}
}

void DelTree(BinTree root)
{
	if (root != NULL){
		DelTree(root->lchild);
		DelTree(root->rchild);
	}
	free(root);
}

BinTree Parent(BinTree bt, char NodeName)
{
	if (bt)
	{
		if (bt->elem == NodeName){
			cout << "�ýڵ�Ϊ���ڵ�" << endl;
			return NULL;
		}

	}
	if ((bt->lchild->elem == NodeName&&bt->lchild != NULL) || (bt->rchild->elem == NodeName&&bt->rchild != NULL))
		return bt;
	else{
		BTNode *tmpP = NULL;
		
	}
}
int main()
{
	int max = 0;
	BinTree root = NULL;
	root = CreateBTree_2();
	//display(root);
	preOrder(root);
	cout << endl;
	inOrder(root);
	cout << endl;
	postOrder(root);
	cout << endl;
	max = maxDepth(root);
	cout << max << endl;
	return 0;
}
//abc##de#g##f###
#endif

#define NULL 0
#include<iostream>
#include<string.h>
#include<cstdio>
#include<stdlib.h>
#include<stack>
using namespace std;
#include<stdio.h>

typedef char datatype;
typedef struct node
{
	datatype elem;
	struct node *lchild, *rchild;
}BTNode, *BinTree;

BinTree CreatBinTree_1(BinTree bt, int isRoot);
BinTree CreatBinTree_2();
void DelTree(BinTree root);
void display(BinTree root);
void preOrder(BinTree root);
void inOrder(BinTree root);
void postOrder(BinTree root);
int maxDepth(BinTree root);
BinTree Parent(BinTree bt, char NodeName);
BinTree Search(BinTree bt, char NodeName);
int Nodes(BinTree bt);
void DispLeaf(BinTree bt);


//����ʽ����������
BinTree CreatBinTree_1(BinTree bt, int isRoot)
{
	char ch;
	if (isRoot)
		printf("Root��");
	fflush(stdin);
	scanf("%c", &ch);
	fflush(stdin);
	if (ch != '#')
	{
		isRoot = 0;
		bt = new BTNode;
		bt->elem = ch;
		bt->lchild = NULL;
		bt->rchild = NULL;
		printf("%c's left child is:", bt->elem);
		bt->lchild = CreatBinTree_1(bt->lchild, isRoot);
		printf("%c's right child is:", bt->elem);
		bt->rchild = CreatBinTree_1(bt->rchild, isRoot);
	}
	return bt;
}

//���򴴽�������
BinTree CreatBinTree_2()
{
	BinTree bt = NULL;
	char ch;
	scanf("%c", &ch);
	if (ch != '#')
	{
		bt = new BTNode;
		bt->elem = ch;
		bt->lchild = CreatBinTree_2();
		bt->rchild = CreatBinTree_2();
	}
	return bt;
}

//ɾ��������
void DelTree(BinTree root)
{
	if (root != NULL)
	{
		DelTree(root->lchild);
		DelTree(root->rchild);
	}
	free(root);
}

//��ʾ���νṹ
void display(BinTree root)
{
	if (root != NULL)
	{
		cout << root->elem;
		if (root->lchild != NULL || root->rchild != NULL)
		{
			cout << '(';
			display(root->lchild);
		}
		if (root->rchild != NULL)
		{
			cout << ',';
			display(root->rchild);
			cout << ')';
		}
	}
}

//�ݹ��������
void preOrder(BinTree root)
{
	if (root != NULL)
	{
		cout << root->elem;
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}

//�ݹ��������
void inOrder(BinTree root)
{
	if (root != NULL)
	{
		inOrder(root->lchild);
		cout << root->elem;
		inOrder(root->rchild);
	}
}

//�ݹ�������
void postOrder(BinTree root)
{
	if (root != NULL)
	{
		postOrder(root->lchild);
		postOrder(root->rchild);
		cout << root->elem;
	}
}

//���������������
int maxDepth(BinTree root)
{
	int m, n;
	if (root == NULL)
		return 0;
	else
	{
		m = maxDepth(root->lchild);
		n = maxDepth(root->rchild);
		if (m>n)
			return(m + 1);
		else
			return(n + 1);
	}
}

//��ѯĳ�����ĸ����
BinTree Parent(BinTree bt, char NodeName)
{
	if (bt)
	{
		if (bt->elem == NodeName)
			cout << "�ý��Ϊ�����" << endl;
		return NULL;
	}
	if ((bt->lchild->elem == NodeName&&bt->lchild != NULL) || (bt->rchild->elem == NodeName&&bt->rchild != NULL))
		return bt;
	else
	{
		BTNode *tempP = NULL;
		if (tempP = Parent(bt->lchild, NodeName))
			return tempP;
		if (tempP = Parent(bt->rchild, NodeName))
			return tempP;
	}
	return NULL;
}

//����ĳ�����
BinTree Search(BinTree bt, char NodeName)
{
	BinTree p;
	if (bt)
	{
		if (bt->elem == NodeName)
			return bt;
		if (bt->lchild)
		{
			p = Search(bt->lchild, NodeName);
			if (p)
				return p;
		}
		if (bt->rchild)
		{
			p = Search(bt->rchild, NodeName);
			if (p)
				return p;
		}
	}
	return NULL;
}

//ͳ�ƶ�����������
int Nodes(BinTree bt)
{
	if (bt == NULL)
		return 0;
	else
		return Nodes(bt->lchild) + Nodes(bt->rchild) + 1;
}

//�������������Ҷ�ӽ��
void DispLeaf(BinTree bt)
{
	if (bt != NULL)
	{
		if (bt->lchild == NULL&&bt->rchild == NULL)
			cout << bt->elem << ' ';
		DispLeaf(bt->lchild);
		DispLeaf(bt->rchild);
	}
}


int main()
{
	BinTree root = NULL;
	root = CreatBinTree_2();
	display(root);
	/*cout << "����˶�������" << endl;
	display(root);
	cout << "\n ��������Ϊ��";
	preOrder(root);
	cout << "\n ��������Ϊ��";
	inOrder(root);
	cout << "\n ��������Ϊ��";
	postOrder(root);
	int num = maxDepth(root);
	cout << "\n �ö����������Ϊ��" << num << endl;
	BinTree nn;
	char name;
	cout << "����Ҫ���ҵĽ������";
	cin >> name;
	nn = Parent(root, name);
	if (nn)
		cout << name << "�ĸ������Ϊ��" << nn->elem << endl;
	nn = Search(root, name);
	if (nn->lchild)
		cout << name << "������Ϊ��" << nn->lchild->elem << endl;
	else
		cout << name << "�����ӡ�" << endl;
	if (nn->rchild)
		cout << name << "���Һ���Ϊ��" << nn->rchild->elem << endl;
	else
		cout << "���Һ��ӡ�" << endl;
	cout << "�˶������Ľ����Ϊ��";
	cout << Nodes(root) << endl;
	cout << "������е�Ҷ�ӽ�㣺\n";*/
	DispLeaf(root);
	system("pause");
	return 0;
}
//abc##de#g##f###
