#define _CRT_SECURE_NO_WARNINGS 1
#include<stdlib.h>
#include<iostream>
using namespace std;

#if 0
#include<queue>
#include<vector>
int main()
{
	vector<int> v{ 2, 5, 1, 6, 3, 9, 8, 0, 7 };
	priority_queue<int> q(v.begin(), v.end());//���ȶ��е�Ĭ�ϵײ�ʵ���ǰ��մ����ʵ�ֵ�
	int size = q.size();
	int i = 0;
	while (i<size)
	{
		cout << q.top() << " ";
		q.pop();
		i++;
	}
	system("pause");
	return 0;
}

#endif



#include<deque>//ջ�Ͷ��еĵײ�ṹʹ��˫�˶���ʵ�ֵ�

#if 0
namespace mine
{
	template<class T, class Container = deque<T>>
	class stack//ջ
	{
	public:
		stack()
		{

		}

		void push(const T&data)
		{
			_con.push_back(data);
		}

		void pop()
		{
			_con.pop_back();
		}

		int size()const
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}

		T&top()
		{
			return _con.back();
		}

		template <class T, class Container = deque<T>>
		class queue
		{
		public:
			queue()
			{}

			void push(const T& data)
			{
				_con.push_back(data);
			}

			void pop()
			{
				_con.pop_front();
			}

			T& front()
			{
				return _con.front();
			}

			const T& front()const
			{
				return _con.front();
			}

			T& back()
			{
				return _con.back();
			}

			const T& back()const
			{
				return _con.back();
			}

			size_t size()const
			{
				return _con.size();
			}

			bool empty()const
			{
				return _con.empty();
			};



		private:
			Container _con;
		};
	};
}
	int main()
	{
		system("pause");
		return 0;
	}

#endif




#include<vector>
#include<functional>
	namespace mine
	{
		template <class T, class Container = vector<T>, class Compare = less<T>>//Ĭ�ϣ�less���������Ǵ��
		class priority_queue
		{
		public:
			priority_queue()
				:c()
			{}

			template<class Iterator>
			priority_queue(Iterator first, Iterator last)//���乹�죬��root�������µ���
				: c(first, last)
			{
				// ��c�е�Ԫ�ص����ɶѵĽṹ
				int count = c.size();
				int root = ((count - 2) >> 1);
				for (; root >= 0; root--)
					AdjustDown(root);
			}

			void push(const T & data)
			{
				c.push_back(data);
				AdjustUP(c.size()-1);//�����±�
			}

			void pop()//ͷɾ�Ļ��Ƚ�ͷԪ�������һ��Ԫ�ؽ����������һ��Ԫ��ɾ������ִ����������
			{
				if (empty())
					return;
				else
				{
					swap(c.front(), c.back());
					c.pop_back();
					AdjustDown(0);
				}
			}
			int size()const
			{
				return c.size();
			}
			bool empty()const
			{
				return c.empty();
			}
			const T & top()const
			{
				return c.front();
			}

		private:

			//��������ϵ��������µ������Ǵ��ģʽ
			void AdjustDown(int parent)//���µ����㷨,�ѽ�СԪ�ص�����ȥ
			{
				int child = parent * 2 + 1;//child�����±�
				while (child < c.size())
				{
					//�ҵ���parentΪ���Ľϴ�ĺ���
					//��������Һ��Ӳ������ӱ��Һ���С����child�����Һ���
					//��child��ʱΪ�ϴ�ĺ���
					if (child + 1 < c.size() && com(c[child], c[child + 1]))
					{
						child = child + 1;
					}
					//������ӽڵ�ȸ��׽ڵ���򽻻�
					if (com(c[parent], c[child]))
					{
						swap(c[child], c[parent]);
						parent = child;
						child = parent * 2 + 1;
					}
					else
						return;
				}
			}

			void AdjustUP(int child)//���ϵ����㷨�����ϴ�Ԫ�ص�����ȥ
			{
				int parent = (child - 1) >> 1;
				while (child)//û�е����Ļ�����ѭ��
				{
					//������׽ڵ�Ⱥ��ӽڵ�С������
					//���ϴ�ڵ��������λ��
					if (com(c[parent], c[child]))
					{
						swap(com(c[parent], c[child]));
						child = parent;
						parent = (child - 1) >> 1;
					}
					else
					{
						return;
					}
				}
			}
		private:
			Container c;
			Compare com;
		};
	}

	int main()
	{
		vector <int> v = { 1, 5, 8, 2, 9, 3, 4, 6 };
		mine::priority_queue <int> q(v.begin(), v.end());
		system("pasue");
		return 0;
	}