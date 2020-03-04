#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<string>
#include<algorithm>

#if 0
bool Is_true(int num)
{
	int i = 1;
	int sum = 0;
	while (i < num){
		if (num%i == 0){
			sum += i;
		}
		i++;
	}
	if (sum == num){
		return true;
	}
	return false;
}
int main()
{
	int n = 0;
	
	while (cin >> n)
	{
		int count = 0;
		int i = 0;
		for (i = 1; i < n; ++i){
			if (Is_true(i)){
				count++;
			}
		}
		cout <<count<<endl;
	}
	system("pause");
	return 0;
}
#endif


#if 0

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> split(string str);
int main()
{
	string a;
	while (getline(cin, a))
	{
		int pos = a.find_first_of("-");
		vector<int> left_one = split(a.substr(0, pos));
		vector<int> right_one = split(a.substr(pos + 1));
		if (left_one[0] == 13 && left_one[1] == 2)          //��߶��� 
			cout << a.substr(0, pos) << endl;               //������   
		else if (right_one[0] == 13 && right_one[1] == 2)   //�ұ߶���  
			cout << a.substr(pos + 1) << endl;              //����ұ� 
		else if (left_one[1] == 4 && right_one[1] != 4)     //���ը�����ұ߲���    
			cout << a.substr(0, pos) << endl;               //������    
		else if (right_one[1] == 4 && left_one[1] != 4)     //�ұ�ը������߲��� 
			cout << a.substr(pos + 1) << endl;              //����ұ�      
		else if (left_one[1] == right_one[1])               //�������  
		if (left_one[0] > right_one[0])
			cout << a.substr(0, pos) << endl;
		else
			cout << a.substr(pos + 1) << endl;
		else
			cout << "ERROR" << endl;
	}
	return 0;
}
vector<int> split(string str)
{
	vector<string> table = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "joker", "JOKER" };
	vector<int>  poker(2, 0);
	//��һλ���ƵĴ�С���ڶ�λ���Ƹ���  
	int pos = str.find_first_of(" ");
	if (pos != -1)
	{
		string temp = str.substr(0, pos);
		if (temp == "10"&&str.substr(pos + 1, 2) != "10")
			//��Ϊֻ�г��˴�С������ֻ��10����λ��      
			poker[1] = 5;
		//����һ����10���ڶ��Ų��ǵ�ʱ��һ����˳��  
		else
			poker[1] = (str.size() + 1) / (temp.size() + 1);
		//�����������ͳһ�����Ƶĸ�������ʹ�ǵ�һ���Ʋ�Ϊ10���м���10��˳�ӣ�ֻ����һ���ƣ�����Ϊ2����ˣ��������    
		poker[0] = find(table.begin(), table.end(), temp) - table.begin();
	}
	else
	{
		poker[1] = 1;
		poker[0] = find(table.begin(), table.end(), str) - table.begin();
	}
	return poker;
}

#endif

#if 0
int main()
{
#if 0
	char a[14] = "abcd";
	char b[5];
	b ="abcd";
#endif
	int i = 3;
	printf("%d %d", ++i, ++i);
	system("pause");
	return 0;
}
#endif


#if 0
void print(char *s)
{
	if (*s)
	{
		print(++s);
		printf("%c", *s);
	}
}

int main()
{ 
	char str[] = "Geneius";
	print(str);
}

#endif

#if 0

class A 
{
public: 
	void FuncA() { printf("FuncA called\n"); }
	virtual void FuncB() { printf("FuncB called\n"); }
};
class B : public A 
{ 
public:
	void FuncA()
	{
		A::FuncA();
		printf("FuncAB called\n");
	}
	virtual void FuncB()	
	{ printf("FuncBB called\n"); }
};
void main(void)
{
	B b; 
	A *pa = &b;
	A *pa2 = new A;
	pa->FuncA();
	pa->FuncB();
	delete pa2;
}
#endif


int main()
{
	string line;
	while (getline(cin, line))
	{
		if (line.find("joker JOKER") != -1){
			cout << "joker JOKER" << endl;
			break;
		}
		int pos = line.find('-');
		//�ֳ�������
		string car1 = line.substr(0, pos);
		string car2 = line.substr(pos + 1);
		//��ȡ�ո�Ĵ���������Ϊ�ո���+1
		int c1 = count(car1.begin(), car1.end(), ' ');
		int c2 = count(car2.begin(), car2.end(), ' ');
		//ȡ����һ����
		string first1 = car1.substr(0, car1.find(' '));
		string first2 = car2.substr(0, car2.find(' '));
		string str = "345678910JQKA2jokerJOKER";
		//������ȣ���ֱ�ӱȽϵ�һ���Ĵ�С
		if (c1 == c2){
			if (str.find(first1) > str.find(first2)){
				cout << car1 << endl;
			}
			else
			{
				cout << car2 << endl;
			}	
		}
		//��������ȣ���˵�����Ͳ�ͬ��ֻ��ը�����������ƱȽϣ�������Ǵ����
		else{
			if (c1 == 3)
				cout << car1 << endl;
			else if (c2 == 3){
				cout << car2 << endl;
			}
			else{
				cout << "ERROR" << endl;
			}
		}
	}
	system("pause");
	return 0;
}