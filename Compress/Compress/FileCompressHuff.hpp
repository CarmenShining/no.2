#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<string>
#include<assert.h>
#include"HuffmanTree.h"

class CharIn
{
public:
	unsigned char _ch;
	int _count;
	std::string _strcode;
	CharIn(int count=0)
	:_count(count){

	}
	CharIn operator +(const CharIn & ch)const{
		return CharIn(ch._count + _count);
	}

	bool operator >(const CharIn & c)const{
		return _count > c._count;
	}

	bool operator ==(const CharIn & c)const {
		return c._count == _count;
	}
};

class FileCompressHuff
{
public:
	FileCompressHuff(){
		for (int i = 0; i < 256; ++i){
			_fileIn.resize(256);
			_fileIn[i]._ch = i;
			_fileIn[i]._count = 0;
		}
	}

	void FileCompresshuff(const std::string & path){
		//1.ͳ��Դ�ļ����ַ���Ϣ
		Done_CharIn_File(path);
		//2.������Ϣ������������
		HuffmanTree<CharIn> t;
		t.CreatHuffmanTree(_fileIn,CharIn(0));
		//3.��ȡ����������
		GetHuffmanCode(t.GetRoot());
		//4.��Դ�ļ���ÿ���ַ������µı����д������ѹ���ļ���
		Compress_File(path);
	}

	void UnFileCompresshuff(const std::string & path){
		FILE *fp3 = fopen("fUnCompre.jpg", "wb");
		FILE *fp2 = fopen(path.c_str(), "rb");
		if (fp2 == nullptr){
			return;
		}

		//��ȡ�ļ���׺
		std::string strPost;
		ReadLine(fp2, strPost);

		//��ȡ�ַ���Ϣ��������
		std::string strCount;
		ReadLine(fp2, strCount);
		int lineCount = atoi(strCount.c_str());

		//��ȡ�ַ���Ϣ
		for (int i = 0; i < lineCount; ++i){
			std::string strCharIn;//�ַ���Ϣ
			ReadLine(fp2, strCharIn);
			//�����ȡ�����ǻ���
			if (strCharIn.empty())
			{
				strCharIn += '\n'; 
				ReadLine(fp2, strCharIn);
			}
			_fileIn[(unsigned char )strCharIn[0]]._count = atoi(strCharIn.c_str() + 2);
		}
		//��ԭ��������
		HuffmanTree<CharIn> t(_fileIn,CharIn(0));

		//��ѹ��
		unsigned char * pReadBuff = new unsigned char[2048];
		char ch = 0;
		HuffmanTreeNode<CharIn> *pCur = t.GetRoot();
		int filesize = pCur->_weight._count;
		int uncount = 0;
		while (true)
		{
			int rdSize = fread(pReadBuff, 1,2048, fp2);
			if (rdSize == 0){
				break;
			}
			for (int i = 0; i < rdSize; ++i){
				//ֻ�轫һ���ֽ��еİ˸�����λ��������
				ch = pReadBuff[i];
				for (int pos = 0; pos < 8; ++pos){
					if (ch & 0x80){
						pCur = pCur->_pright;
					}
					else{
						pCur = pCur->_pleft;
					}
					ch <<= 1;
					if (nullptr == pCur->_pleft&&nullptr == pCur->_pright){
						uncount++;
						fputc(pCur->_weight._ch, fp3);
						if (uncount == filesize){
							break;
						}
						pCur = t.GetRoot();
					}
				}
			}
		}
		delete[] pReadBuff;
		fclose(fp2);
		fclose(fp3);
	}
private:
	void Done_CharIn_File(const std::string & path)
	{
		FILE *fIn = fopen(path.c_str(), "r");
		if (nullptr == fIn){
			assert(false);
			return;
		}
		unsigned char * readBuff = new unsigned char[1024];
		int readSize = 0;
		while (1){
			readSize = fread(readBuff, 1, 1, fIn);
			if (readSize == 0){
				break;
			}
			//ͳ��
			for (int i = 0; i < readSize; ++i){
				_fileIn[readBuff[i]]._count++;
			}
		}
		delete[] readBuff;
		fclose(fIn);
	}

	//��ȡ����������
	void GetHuffmanCode(HuffmanTreeNode<CharIn>* proot){
		typedef HuffmanTreeNode<CharIn> Node;
		std::string strCode;
		if (proot == nullptr){
			return;
		}
		GetHuffmanCode(proot->_pleft);
		GetHuffmanCode(proot->_pright);
		if (nullptr==proot->_pleft &&nullptr == proot->_pright){
			Node * cur = proot;
			Node * parent = proot->_pparent; 
			while (parent){
				if (cur == parent->_pleft){
					strCode += '0';
				}
				else{
					strCode += '1';
				}
				cur = parent;
				parent = cur->_pparent;
			}	
			reverse(strCode.begin(), strCode.end());
			_fileIn[proot->_weight._ch]._strcode = strCode;
		}
	}
	
	//��Դ�ļ���ÿ���ַ������µı����д������ѹ���ļ���
	void Compress_File(const std::string &path){
		FILE*fIn=fopen(path.c_str(), "rb");
		FILE*fCompre = fopen("fCompre.TXT", "wb");
		//��ѹ���ļ��в���Ҫ����ѹ����Ϣ������Ҫ�����ļ��ĺ�׺���ַ���Ϣ���������ַ����ֵĴ���
		WriteHead(fCompre,path);

		fseek(fIn, 0, SEEK_SET);
		//���¶�ȡ�ļ��е���Ϣ
		unsigned char * readBuff = new unsigned char[2048];
		int readSize = 0;
		char ch = 0;
		int bitCount = 0;
		while (true){
			readSize = fread(readBuff, 1, 2048, fIn);
			if (readSize == 0){
				break;
			}
			//�Ѿ�������
			for (int i = 0; i < readSize; ++i){
				std::string newStrCode = _fileIn[readBuff[i]]._strcode;
				for (int j = 0; j < newStrCode.size(); ++j){
					ch <<= 1;
					if (newStrCode[j] == '1'){
						ch |= 1;
					}
					
					bitCount++;
					if (bitCount == 8){
						fputc(ch, fCompre);
						ch = 0;
						bitCount = 0;
					}
				}
			}
		}
		if (bitCount > 0){
			ch = ch << (8 - bitCount);
			fputc(ch, fCompre);
		}
		delete[] readBuff;
		fclose(fCompre);
		fclose(fIn);
	}

	//���ѹ���ļ��е�ͷ����Ϣ
	void WriteHead(FILE * fCompress, const std::string &path ){

		std::string filePost;//�ļ���׺
		filePost=path.substr(path.rfind('.'));//��ȡ�ļ���׺
		//�ѽ�ȡ�����ļ���׺��д��ѹ���ļ���
		fwrite(filePost.c_str(), 1, filePost.size(), fCompress);
		fwrite("\n", 1, 1, fCompress);


		//���������ַ����ֵĴ���д��ѹ���ļ���
		int count = 0;//����
		std::string CharIn;//�ַ���Ϣ
		char Itoa[32] = { 0 };
		for (int i = 0; i < 256; ++i){
			if (_fileIn[i]._count != 0){
				count++;
				CharIn += _fileIn[i]._ch;
				CharIn += ':';
				CharIn += _itoa(_fileIn[i]._count, Itoa, 10);
				CharIn += '\n';
			}
		}
		fwrite(_itoa(count,Itoa,10), 4, 1, fCompress);
		fwrite("\n", 1, 1, fCompress);
		fwrite(CharIn.c_str(), 1, CharIn.size(), fCompress);
	}

	void ReadLine(FILE * fp, std::string & StrInfo)
	{
		while (!feof(fp))
		{
			char ch = fgetc(fp);
			if (ch == '\n')
				break;
			StrInfo += ch;
		}
	}


private:
	std::vector<CharIn> _fileIn;
};