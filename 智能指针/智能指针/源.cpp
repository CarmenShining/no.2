#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

#if 0
template<class T>
class SmartPtr
{
public:
	SmartPtr(T * p=nullptr)
		:_ptr(p)
	{}
	~SmartPtr()
	{
		if (_ptr){
			delete _ptr;
		}
	}
	T &operator*()
	{
		return *_ptr;
	}
	T * operator->()
	{
		return _str;
	}
private:
	T* _ptr;
};

int main()
{
	SmartPtr<int> p1(new int);
	SmartPtr<int> p2(p1);
	system("pause");
	return 0;
}
#endif


#if 0
#include<memory>
int main()
{
	auto_ptr<int> p1(new int);
	*p1 = 1;
	auto_ptr<int> p2(p1);
	cout << *p1 << endl;
	cout << *p2 << endl;
	system("pause");
	return 0;
}
#endif 


#if 0
template<class T>
class SmartPtr
{
public:
	SmartPtr(T * p = nullptr)
		:_ptr(p)
	{}
	~SmartPtr()
	{
		if (_ptr){
			delete _ptr;
		}
	}
	SmartPtr(SmartPtr<T> & p)
		:_ptr(p._ptr)
	{
		p._ptr = nullptr;

	}
	SmartPtr<T>& operator=(SmartPtr<T> & p)
	{
		if (this != &p)
		{
			//�����ǰ��������Դ�Ƚ���ǰ��Դ�ͷ�
			if (_ptr){//���_ptr������Դ���Ƚ��Լ�����Դ�ͷţ����������ڴ�й©
				delete _ptr;
			}
			_ptr = p._ptr;
			p._ptr = nullptr;
		}
		return *this;
	}
	T &operator*()
	{
		return *_ptr;
	}
	T * operator->()
	{
		return _str;
	}
private:
	T* _ptr;
};

int main()
{
	SmartPtr<int> p1(new int);
	SmartPtr<int> p2(p1);
	SmartPtr<int> p3(new int);
	SmartPtr<int> p2 = p3;//���ָ�ֵ������ڶ���if������

	system("pause");
	return 0;
}
#endif


#if 0
template<class T>
class SmartPtr
{
public:
	SmartPtr(T * p = nullptr)
		:_ptr(p)
		, _owner(false)
	{
		if (_ptr){
			_owner = true;
		}
	}

	~SmartPtr()
	{
		if (_ptr&&_owner){
			delete _ptr;
			_ptr = nullptr;
		}
	}

	SmartPtr(SmartPtr<T> & p)
		:_ptr(p._ptr)
		, _owner(p._owner)//��_owener���£����Կ�������ֻ�ͷ�_ownerΪtrue��
		//�����ǳ����������
	{
		p._owner = false;
	}
	SmartPtr<T>& operator=(SmartPtr<T> & p)
	{
		if (this != &p){
			//�����ǰ�����������Դ�Ȱ����ͷ�
			if (_ptr){
				delete _ptr;
			}
			_ptr = p._ptr;//��Դת��
			_owner = p._owner;//�ͷ�Ȩ��ת��
			p._owner = false;
		}
	}
	T &operator*()
	{
		return *_ptr;
	}
	T * operator->()
	{
		return _str;
	}
private:
	T* _ptr;
	bool _owner;
};

#include<memory>
int main()
{
	SmartPtr<int> p1(new int);
	if (1){
		SmartPtr<int> p2(p1);
		*p2 = 10;
	}
	//p1��Ұָ��
	*p1 = 20;
	
	system("pause");
	return 0;
}
#endif

#include<memory>

#if 0
int main()
{
	unique_ptr<int> p1(new int);
	//����
	unique_ptr<int> p2(p1);
	unique_ptr<int> p3(new int);
	//����
	p3 = p1;
	system("pause"); 
	return 0;
}
#endif


#if 0
template<class T>
class mine{
	class unique_ptr
	{
	public:
		unique_ptr(T * p = nullptr)
			:_ptr(p)
			, _owner(false)
		{
			if (_ptr){
				_owner = true;
			}
		}

		~unique_ptr()
		{
			if (_ptr&&_owner){
				delete _ptr;
				_ptr = nullptr;
			}
		}

		T &operator*()
		{
			return *_ptr;
		}
		T * operator->()
		{
			return _str;
		}
	/*private:
		unique_ptr(unique_ptr<T> & p){};
		unique_ptr<T> &operator=(unique_ptr<T> &p){};*/
		
		//c++11
		unique_ptr(const unique_ptr<T> &p) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
	private:
		T* _ptr;
		bool _owner;
	};
};

#endif

#if 0

#include <memory>

template<class T>
class DFDef
{
public:
	void operator()(T*& p)//���������أ�ֻ��Ҫ����һ��T���Ͷ����ָ��
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

template<class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = nullptr;
		}
	}
};


class FClose
{
public:
	void operator()(FILE*& p)
	{
		if (p)
		{
			fclose(p);
			p = nullptr;
		}
	}
};

namespace Mine
{
	template<class T, class DF = DFDef<T>>//DF��һ���Զ�������ģ�壬Ĭ�ϵ���DFDef
	class unique_ptr
	{
	public:
		// RAII
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				//delete _ptr; // �ͷ���Դ�ķ�ʽ�̶����ˣ�ֻ�ܹ���new����Դ�����ܴ����������͵���Դ
				//DF()(_ptr);
				DF df;//����һ��DF����
				df(_ptr);//����df�еģ������أ�����ָ��
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		unique_ptr(const unique_ptr<T>&) = delete;  // 1. �ͷ�new�Ŀռ�  2.Ĭ�ϳ�Ա���� = delete �� ���߱�������ɾ����Ĭ�ϳ�Ա����
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

	private:
		T* _ptr;
	};
}

#include<malloc.h>
void TestUniquePtr()
{
	//ͨ��ģ������б�ĵڶ���������ѡ��������ʱѡ���Ӧ����������
	Mine::unique_ptr<int> up1(new int);
	Mine::unique_ptr<int, Free<int>> up2((int*)malloc(sizeof(int)));//��һ�����ȥ
	Mine::unique_ptr<FILE, FClose> up3(fopen("1.txt", "w"));
}

int main()
{
	TestUniquePtr();
	return 0;
}
#endif


#if 0
//ģ��ʵ��shared_ptr
//����дʱ�������ǳ����

template<class T>
class DFDef
{
public:
	void operator()(T*&ptr){
		if (ptr){
			delete ptr;
			ptr = nullptr;
		}
	}
};
namespace Mine
{
	template<class T,class DF=DFDef<T>>
	class shared_ptr
	{
	public:
		shared_ptr(T*ptr = nullptr)
			:_ptr(ptr)
			, _pCount(nullptr)
		{
			if (_ptr){
				_pCount = new int(1);//��_ptr��Ϊ��ʱ��_pCount��ֵΪ1
			}
		}

		~shared_ptr()
		{
			//������>0ʱֻ��_pCount--
			//����Ϊ0ʱ˵����ǰ��Դ�������һ��������ʹ�ã���ʱ�ɵ�ǰ�����ͷ���Դ
			if (_ptr && 0 == --(*_pCount)){
				//delete _ptr;
				DF df;
				df(_ptr);
				delete _pCount;
			}
		}

		T& operator *()
		{
			return *_ptr;
		}

		T*operator->()
		{
			return _ptr;
		}

		//�������캯���͸�ֵ����������ؾ���Ҫ���Ǽ�����������
		shared_ptr(const shared_ptr<T> &sp)
			:_ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr){
				++(*_pCount);
			}
		}

		shared_ptr<T> & operator=(const shared_ptr<T> &sp)
		{
			if (this != &sp){
				//1.���������Դ�Ͽ���ϵ(����������һ��ʹ����Դ�Ķ����ֻ�ü�����һ����������һ��ʹ����Դ�Ķ������ͷ���Դ)
				if (_ptr && 0 == -(*_pCount)){
					delete _ptr;
					delete _pCount;
				}
				//2.��sp������Դ�ͼ���
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr){
					++*_pCount;
				}
			}
			return *this;
		}

		int use_count()
		{
			return *_pCount;
		}
	private:
		T*_ptr;
		int *_pCount;
	};
}



void TestShradPtr()
{
	Mine::shared_ptr<int> sp1(new int);
	cout << sp1.use_count() << endl;

	Mine::shared_ptr<int> sp2(sp1);
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;


	Mine::shared_ptr<int> sp3(new int);
	cout << sp3.use_count() << endl;

	Mine::shared_ptr<int> sp4(sp3);
	cout << sp3.use_count() << endl;
	cout << sp4.use_count() << endl;

	sp3 = sp2;
	cout << sp2.use_count() << endl;
	cout << sp3.use_count() << endl;

	sp4 = sp2;
	cout << sp2.use_count() << endl;
	cout << sp4.use_count() << endl;
}


int main()
{
	TestShradPtr();
	system("pause");
	return 0;
}
#endif


