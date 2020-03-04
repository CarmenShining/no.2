#define _CRT_SECURE_NO_WARNINGS 1
#include"LZHashTable.h"
#include"Common.h"
#include<cstring>

const USH HASH_BITS  = 15;
const USH HASH_SIZE = (1 << HASH_BITS);
const USH HASH_MASK = HASH_SIZE - 1;//���룬��֤�±겻��Խ��
 
LZHashTable::LZHashTable(USH size)
:_prev(new USH[size * 2])
, _head(_prev + size){
	memset(_prev, 0, size * 2 * sizeof(USH));
}

LZHashTable::~LZHashTable(){
	delete[] _prev;
	_prev = nullptr;
}

//hashAddr����ǰһ�μ�����Ĺ�ϣ��ַ
//ch������ƥ����ַ��������һ���ַ�
//��һ�μ�����Ĺ�ϣ��ַ�Ѿ�������
//���磺abcdefg
//hashAddrʱabc�ĵ�ַ
//����Ҫ����bcd�Ĺ�ϣ��ַ��ֻ��Ҫ��d�ַ�����Ϳ�
void LZHashTable::HashFunc(USH& hashAddr, UCH ch){
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK;
}

USH LZHashTable::H_SHIFT(){
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}


// hashAddr����һ�ι�ϣ��ַ              ch�����л�������һ���ַ� 
// pos��ch�ڻ��������е�λ��             matchHead�����ƥ�䣬����ƥ�䴮����ʼλ��
void LZHashTable::Insert(USH& macthHead,UCH ch, USH pos,USH& hashAddr){
	// �����ϣ��ַ
	HashFunc(hashAddr, ch);
	// ����ѹ���Ĳ��Ͻ��У�pos�϶������WSIZE������WMASK��֤��Խ��
	_prev[pos & HASH_MASK] = _head[hashAddr];
	macthHead = _head[hashAddr]; 
	_head[hashAddr] = pos;
}

USH LZHashTable::GetNext(USH matchHead){
	return _prev[matchHead&HASH_MASK];
}

void LZHashTable::Update(){
	for (USH i = 0; i < WSIZE; ++i){
		//����head
		if (_head[i] >= WSIZE){
			_head[i] -= WSIZE;
		}
		else{
			_head[i] = 0;
		}
		//����prev
		if (_prev[i] >= WSIZE){
			_prev[i] -= WSIZE;
		}
		else{
			_prev[i] = 0;
		}
	}
}