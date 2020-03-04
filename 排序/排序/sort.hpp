#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<vector>
#include<windows.h>
#include<iostream>

//ÿ��ѡ����С����ǰ��
class SelectSort
{
public:
	static std::vector<int> selectSort(std::vector<int>& v){
		int i = 0;
		int j = 0;
		for (i = 0; i < v.size(); ++i){
			int min = i;
			for (j = i+1; j < v.size() ; j++){
				if (v[j] < v[min]){
					min = j;
				}
			}
			int tmp = v[i];
			v[i] = v[min];
			v[min] = tmp;
		}
		return v;
	}
};

//�������򣬴ӵڶ���Ԫ�ؿ�ʼ�������Ԫ�ص�ָ�ȼ�¼����
//Ȼ����ǰ�ҵ���һ�����������Ԫ���������λ�þ��������
class InsertSort
{
public:
	static std::vector<int> Insertsort(std::vector<int> &v){
		if (v.size() < 2){
			//��ֻ��һ��Ԫ�ص�ʱ��ֱ�ӷ���
			return v;
		}
		//���в���
		for (int i = 1; i < v.size(); ++i){
			int tmp = v[i];
			int k = i - 1;//
			while (k >= 0 && v[k]>tmp){
				k--;
			}
			//��ʱ�Ѿ��ҵ�����λ��Ϊk+1,��λ���ڳ�������Ԫ�ز����ȥ
			for (int j = i; j >k+1; j--){
				v[j] = v[j - 1];
			}
			v[k+1] = tmp;
		}
		return v;
	}
};

//ϣ����������ڲ�������Ļ����ϼ���������ʹԭ���и�������߳���Ч��
class ShellSort
{
public:
	static void Shellsort(std::vector<int> & v){
		//��������gap
		int gap = v.size()/2;
		for (gap; gap >0; gap/=2){
			//�ڷ�����ʹ�ò���,�ӵ�gap��Ԫ�ؿ�ʼ����������ڷ�����в���
			for (int i = gap; i < v.size(); ++i){
				int j = i;
				int tmp = v[j];
				if (v[j] < v[j - gap]){
					while (j - gap >= 0 && v[j] < v[j - gap]){
						v[j] = v[j - gap];
						j -= gap;
					}
					v[j] = tmp;
				}
			}
		}
	}
};



class BubbleSort
{
public:
	static void Bubblesort(std::vector<int> & v){
		if (v.size() < 2){
			return;
		}
		//flag�������ǣ����һ��ð�ݶ�û�з���˵����ʱ�������������ֱ�ӷ��ز���Ҫ�ټ���ѭ��
		bool flag=true;
		for (int i = 0; i < v.size(); ++i){
			//�ڶ���ѭ����ʾ��i����Ҫ�Ĵ�����n-i-1
			for (int j = 0; j < v.size()-i-1; ++j){
				if (v[j+1] < v[j]){
					int tmp = v[j];
					v[j] = v[j+1];
					v[j+1] = tmp;
					flag = false;
				}
			}
			if (flag){
				break;
			}
		}
	}
};

//�鲢�����˼���ǽ����ж԰�ֳ�����������������ٺϲ�
class MergeSort
{
public:
	static std::vector<int> Mergesort(std::vector<int> v, int left, int right){
		if (left < right){
			//�������Ϊ����������
			int mid = (right - left) / 2;
			//����ߵ������������
			v=Mergesort(v, left, mid);
			//���ұߵ������������
			v=Mergesort(v, mid + 1, right);
			//�ϲ�
			merge(v, left, mid, right);
		}
		return v;
	}

	static void merge(std::vector<int> &v, int left, int mid, int right){
		std::vector<int> tmp;
		tmp.resize(right-left+1);
		int i = 0;
		int j = left;
		int k = mid+1;
		while (j <= mid&&k <= right){
			if (v[j] <	v[k]){
				tmp[i++] = v[j++];
			}
			else{
				tmp[i++] = v[k++];
			}
		}
		while (j <= mid){
			tmp[i++] = v[j++];
		}
		while (k <= right){
			tmp[i++] = v[k++];
		}
			v = tmp;
	}
};



