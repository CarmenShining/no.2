#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#if 0
#include<string>
#include<algorithm>
int main()
{
    string s;
    while(getline(cin,s))
    {
		reverse(s.begin(),s.end());
        auto start=s.begin();
        auto finish=s.begin();
        while(1)
        {
			if (finish == s.end())
			{
				reverse(start, finish);
				break;
			}
			if (!((*finish >= 'a'&&*finish <= 'z')||(*finish >= 'A'&&*finish <= 'Z')))
             {
				*finish = ' ';
                 reverse(start,finish);
                 finish++;
                 start=finish;
             }
            else{
                finish++;
            }
        }
		auto it = s.begin();
		while (*it == ' ')
		{
			it++;
		}
        //cout<<s<<endl;
		while (it != s.end())
		{
			cout << *it;
			it++;
		}
		cout << endl;
        s.clear();
    }
    return 0;
}

//$bo*y gi!r#l #

#endif

//DABDA  CADBB


#if 0
#include<iostream>
using namespace std;
#include<string>
int main()
{
	string s1 = "";
	string s2 = "0123456789ABCDEF";//���ֶ��巽ʽ��Ϊ�˱�ʾ16����
	int num = 0;
	int x = 0;
	while (cin >> num >> x)
	{
		if (num < 0)
		{
			num = -num;
			cout << "-";
		}
		//��31%16ʱ������15����ΪҪ��ʾ��16���Ƶĸ�ʽ����Ҫ��s2�ַ����ж�Ӧ
		for (int i = num; i; i /= x)
		{
			s1 = s2[i%x] + s1;//s1��Ϊ����ַ�����ÿ�ΰ�i%x��s2�еĶ�Ӧ����ӵ�s1��
		}
		cout << s1 << endl;
		s1.clear();
		s2.clear();
	}
	return 0;
}

#endif


#if 0
int main()
{
	int a = 0; int b = 0; int c = 0; int d = 0;
	while (cin >> a >> b >> c>>d)
	{
		int A = (a + c) / 2;
		int B = (b + d) / 2;
		int C = (d-b)/2;
		if (A - B == a && B - C == b && A + B == c && B + C == d)//�ж��Ƿ������ϵʽ��������ȥ�Ϳ���֤
		{ cout << A << " " << B << " " << C << endl; }
		else
		{
			cout << "No" << endl;
		}
	}
	system("pause");
	return 0;
}
#endif


#include<stdio.h> 
int cnt=0;
int fib(int n)
{
	cnt++;  
	if(n==0)
		return 1;  
	else if(n==1)    
		return 2;
	else      
		return fib(n-1)+fib(n-2);
} 
void main()
{
	fib(8);
	printf("%d", cnt);
}