#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include"Common.hpp"
#include<vector>



//****ʵ�ֵ��ǲ��ظ����ֵĹ�ϣ��(��ɢ��)*****

//��ϣ��ÿ��λ�õı��
enum State{EMPTY,EXIST,DELETE};

template<class T>
class HushElem
{
public:
	HushElem(const T& data=T())
	:_data(data)
	,_st(EMPTY)
	{}
	T _data;
	State _st;
};

template<class T>
class Hushtable
{
public:
	Hushtable(const int capacity=13)
		:_size(0)
		,_total(0){
		_ht.resize(capacity);
	}

	bool Insert(const T&data){
		//ͨ����ϣ�����������ϣ��ַ
		int hushAddr = HushFunc(data);
		int count = 0;
		//�ж������ַ�Ƿ���ã����룻����̽��
		while (_ht[hushAddr]._st != EMPTY){
			//�����ַ�ǲ����õģ�����Ҫ��������̽��
			if (_ht[hushAddr]._st==EXIST&&_ht[hushAddr]._data == data){
				return false;//��Ҫ�����Ԫ���Ѿ������ڹ�ϣ����ʱ��ֱ�ӷ�����
			}
			
			//��������ϣ��ͻʱ������̽��Ͷ���̽��
			//1.����̽�⣬ֱ�ӶԵ�ַ++
			hushAddr++;
			if (hushAddr == _ht.size()-1){
				hushAddr = 0;
			}
			//2.����̽�⣬�Լ�����Ĺ�ϣ��ַƽ��
#if 0
			count++;
			hushAddr = (hushAddr + (2 * i + 1))%_ht.capacity();
#endif
		}
		_ht[hushAddr]._data = data;
		_ht[hushAddr]._st = EXIST;
		_size++;
		_total++;
		return true;
	}

	int Find(const T&data){
		int hushAddr = HushFunc(data);
		while(_ht[hushAddr]._st != EMPTY){
			if (_ht[hushAddr]._st == EXIST&&_ht[hushAddr]._data==data){
				return hushAddr;
			}
			if (hushAddr == _ht.size()-1){
				hushAddr = 0;
				continue;
			}
			hushAddr++;
		}
		return -1;
	}

	bool Earse(const T& data){
		int hushAddr = Find(data);
		if (hushAddr != -1){
			_ht[hushAddr]._st = DELETE;
			_size--;
			return true;
		}
		return false;
	}

private:
	//��ϣ�����������ϣ��ַ
	int HushFunc(const T&data = T()){
		//����dataģ�ϲ�����������ӽ�����һ������
		return data % 10;
	}

	bool CheckCapacity(){
		//���ֱ�ӽ��г�������Ϊ0������Ҫ���������x10
		if ((_total * 10) / _ht.capacity() >= 7){
			//�������Ѿ����ڹ�ϣ�������ʱ��Ҫ����
			//1.�����¿ռ�
			//ushElem<T> tmp = new HushElem<T>(GetNextPrime(_ht.capacity));
			HushElem<T> tmp(GetNextPrime(_ht.capacity()));
			//2.���ɿռ��Ԫ�ذ��չ�ϣ��ַ�ŵ��¿ռ���
			for (auto e & _ht){
				if (e._st == EXIST){
					tmp.Insert(e);
				}
			}
			//3.�����¾ɿռ�
			_ht.swap(tmp);
		}
		return false;
	}

private:
	std::vector<HushElem<T>> _ht;
	int _size;
	int _total;
};