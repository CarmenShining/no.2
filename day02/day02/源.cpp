
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
#if 0
int main()
{
	string s;
	while (getline(cin, s))
	{
		reverse(s.begin(), s.end());
		auto start = s.begin();
		auto finish = s.begin();
		while (1)
		{
			if (finish == s.end())
			{
				reverse(start, finish);
				break;
			}
			if (*(finish) == ' ')
			{
				reverse(start, finish);
				finish++;
				start = finish;
			}
			else
			{
				finish++;
			}
		}
		cout << s << endl;
		s.clear();
	}
	system("pause");
	return 0;
}
#endif


#if 0
#include<vector>
int main()
{
	vector<int> A;
	int n = 0;
	int tmp;
	int min = 0;
	int num = 0;
	int flag = 0;
	while (cin >> n)
	{	
		while (cin >> tmp)
		{
			A.push_back(tmp);
		}
		
		auto it = A.begin();
		while (it != A.end())
		{
			num = *it;
			if (*(it + 1) > *it )
			{
				flag = 1;//����
			}
			else if (*(it + 1) < *it)
			{
				flag = -1;//����
			}
			else//���
			{
				for (it; *(it + 1) == *it; it++)
				{
					if (*(it + 1) > *it)
					{
						flag = 1;//����
						break;
					}
					else if (*(it + 1) < *it)
					{
						flag = -1;//����
						break;
					}
				}
			}
			if (flag == 1)
			{
				if (*(it + 1) >= *it)
				{
					it++;
				}
				else
				{
					min++;
					it++;
				}
			}
			if (flag == -1)
			{
				if (*(it + 1) <= *it)
				{
					it++;
				}
				else
				{
					min++;
					it++;
				}
			}
		}
		cout << min << endl;
	}
	system("pause");
	return 0;
}
#endif

#if 0
//λ�εĲ���
struct A
{
	int a : 2;//32��bit�е�2��bit
	int b : 5;//32��bit�е�5��bit
	int c : 10;//32��bit�е�10��bit
	int d : 30;//32��bit�е�30��bit
};
int main()
{
	cout << sizeof(A) << endl;
	system("pause");
	return 0;
}
#endif


#if 0
#include<iostream>
using namespace std;
#include<vector>
int main()
{
	int n = 0;
	vector<int> v;
	int i = 0;
	while (cin >> n)
	{
		v.resize(n + 1);
		for (i = 0; i<n; i++)
		{
			cin >> v[i];
		}
		i = 0;
		int count = 0;
		while (i<n)
		{
			if (v[i + 1]>v[i])//����
			{
				while (v[i + 1] >= v[i] && i < n)
				{
					i++;
				}
				//����ѭ����˵���ҵ��˼�С���Ǹ�������count++��i++����������
				count++;
				i++;
			}
			else if (v[i + 1] == v[i])
			{
				i++;
			}
			else
			{

				while (v[i + 1] <= v[i] && i < n)
				{
					i++;
				}
				count++;
				i++;
			}
		}
		cout << count << endl;
		v.clear();
	}
	return 0;
}
#endif



#include<string>

int main()
{
	string s1 = "ok";
	string s2 = "fine";
	//s2 = s1+" "+s2;
	s2 = s2 + " " + s1;
	cout << s2<<endl;
	system("pause");
	return 0;
}