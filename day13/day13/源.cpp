#define _CRT_SECURE_NO_WARNINGS 1
#if 0
#include<iostream>
using namespace std;
#include<string>
#include<vector>

int main()
{
	string s;
	while (getline(cin, s))
	{
		int i = 0; int count = 0;
		vector<string> v;
		int j = 0;
		auto it = s.begin();
		for (i = 0; i < s.size(); i++){
			if (s[i] == ' ')count++;
			if (s[i] == '"'){
				for (j = i+1; s[j] != '"'; j++){

				}
				i =j;
			}
		}
		cout << count+1 << endl;
		auto start = s.begin();
		auto finish = s.begin();
		while (start != s.end()&&finish!=s.end()){
			if (*finish == ' '){
				while(start!=finish){
					cout << *start;
					start++;
				}
				finish++;
				start = finish;
				cout << endl;
				continue;
			}
			else if (*start == '"'){
				start++;
				finish++;
				while (*finish != '"'){
					finish++;
				}
				while (start != finish){
					cout << *start;
					start++;
				}
				finish++;
				start = finish;
				
				continue;
			}
			finish++;
		}
		while (start != finish){
			cout << *start;
			start++;
		}
	}
	system("pause");
	return 0;
}
#endif



#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define INT_MAX 100001
int main()
{    int n, m; 
while(cin >> n >> m) 
{     
	vector<int> dp(m + 1, INT_MAX);
	//dp[i]Ϊ�ڵ�i��ʯ��ʱ������Ҫ�Ĳ�������ʼ��Ϊ������Χ�ڵ����ֵ     
	dp[n] = 0;
	for (int i = n; i <= m; i++)
	{  
		for (int j = 2; j*j <= i; j++) 
			//����iΪ8�����ҵ�i��һ��Լ��jΪ2ʱ����һ��Լ����Ϊi/j  
		{
			//����ֻ��Ҫ��j*j<=i,��ʵ��������������������������г�ʱ    
			if (i%j == 0)
			{  
				if (i + j <= m)  
					dp[i + j] = min(dp[i + j],dp[i]+1); 
				if(i+i/j<=m) //�ؼ�����      
					dp[i + i/j] = min(dp[i + i/j],dp[i]+1);   
			}
		}
	}
	if(dp[m]==INT_MAX)      
		cout<<"-1"<<endl;  
	else 
		cout<<dp[m]<<endl;
}
return 0;
}
