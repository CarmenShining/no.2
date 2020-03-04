#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<string>
using namespace std;
#include<vector>
#if 1
struct CharInfo
{
	//CharInfo()
	//:_ch('0')
	//, _count(0)
	//, _strcode("")
	//{
	//}

	unsigned char _ch;//�����ַ�
	int _count;//�ַ����ֵ�����
	string _strcode;//�ַ��ı���
};


class FileCompressHuff
{
public:
	FileCompressHuff();
	void CompressFile();
	void UnCompressFile();
private:
	void ReadLine(FILE * fp, std::string & StrInfo);
private:
	vector<CharInfo> _fileInfo;
};

#endif


#if 0
class CharIn
{
public:
	CharIn()
	{
		for (int i = 0; i < sizeof(arr); ++i)
		{
			arr[i] = 0;
		}
	}
	char ch;
	char arr[256];
	int count;
};

class Out
{
public:
	char ch;

};



class File
{
public:
	void TJFileIO()
	{
		CharIn charin;
		char buf[1024] = { 0 };
		int ret = 1;
		FILE *fp = fopen("1.TXT", "r");
		while (ret)
		{
			ret = fread(buf, 1024, 1, fp);//ÿ�ζ�ȡ1024���ֽڣ���ȡһ�Σ��������ļ�ĩβ�򷵻�ֵΪ0���˳�
			for (int i = 0; i < sizeof(buf); ++i)
			{
				charin.arr[buf[i]]++;//arr��Ԫ�صĶ�Ӧ��ֵ��Ϊ���ַ����ֵĴ������±��Ӧ�ַ�ASCII��ֵ��
			}
			for (int i = 0; i < sizeof(charin.arr); ++i)
			{
				if (charin.arr[i] == 0){
					continue;
				}
				charin.ch = i;
			}
		}


		fclose(fp);
	}

};
#endif