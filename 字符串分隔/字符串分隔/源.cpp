#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<string>
void fun(string & s,string & s3)
{
	int size1 = s.size();
	while (size1>8)//�����ڰ˸�ʱ����Ҫ���0
	{
		s3.insert(s3.size(), s, 0, 8);//��s3.size()��λ�ò���s��λ��0��ʼ��8���ֽ�
		s3.push_back('\n');//����
		size1 -= 8;
		s.erase(0, 8);//��sǰ8��Ԫ�ز�ȥ
	}
	int newsize1 = s.size();
	s3.insert(s3.size(), s, 0, newsize1);//��s��ʣ�ಿ����ӵ�s3��
	s3.insert(s3.size(), 8 - newsize1, '0');//s3��ʣ�ಿ����0����
	s3.push_back('\n');
}


int main()
{
	string s1;
	string s2;
	string news;
	int i = 0;
	int pos = 0;
	while (cin >> s1&&cin >> s2)
	{
		fun(s1, news);
		fun(s2, news);
	}
	cout << news;
	system("pause");
	return 0;
}