#define _CRT_SECURE_NO_WARNINGS 1
 #include<iostream>
 using namespace std;
 #include<stack>
#include<vector>
 int main()//��STL�е�stack������������ջ�������
{
 stack<int> s;
 int num;
 while (cin >> num)
 {
	 if (num != -1)
	 {
		 s.push(num);
	 }
	 else
	 {
		 cout << s.top();
		 s.pop();
	 }
 }
 return 0;
}

