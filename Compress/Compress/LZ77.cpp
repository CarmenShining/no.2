#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"LZ77.h"
#include<assert.h>

const USH MIN_LOOKAHEAD = MAX_MATCH + MIN_MATCH + 1;
const USH MAX_DIST = WSIZE - MIN_LOOKAHEAD;


LZ77::LZ77()
:_pWin(new UCH[WSIZE*2])
,_ht(WSIZE){

}

LZ77::~LZ77(){
	delete[] _pWin;
	_pWin = nullptr;
}



void LZ77::CompressFile(const std::string &path){
	//���Ƚ�Դ�ļ��򿪣���Դ�ļ����ַ�С�������Ͳ�����ѹ����
	FILE*fIn=fopen(path.c_str(), "rb");
	if (nullptr == fIn){
		std::cout << "���ļ�ʧ��" << std::endl;
	}
	fseek(fIn, 0, SEEK_END);
	ULL FileSize=ftell(fIn);
	if (FileSize <= MIN_MATCH){
		std::cout << "�ļ���С������ѹ��" << std::endl;
		return;
	}

	//��ѹ���ļ��ж�ȡһ�������������ݵ�������
	fseek(fIn, 0, SEEK_SET);
	//���ļ��ж�ȡ��������Ϊһ���������Ĵ�С
	int lookAhead=fread(_pWin, 1, 2 * WSIZE, fIn);

	//���ڹ�ϣ������Ҫ����ǰ��Ĺ�ϣ��ַ�͵�ǰ�ֽڼ����
	//�����Ƚ�ǰ�����ֽڵĹ�ϣ��ַ�����
	USH start = 0;//�Ӵ��ڵ�����࿪ʼ����
	USH hashAddr = 0;
	for (USH i = 0; i < MIN_MATCH-1; ++i){
		_ht.HashFunc(hashAddr, _pWin[i]);
	}

	//��ʼѹ��
	FILE * fOut = fopen("Compress.TXT", "wb");

	assert(fOut);


	//�򿪱���ļ�
	FILE* fFlag = fopen("Flag.txt", "wb");

	//��������ƥ���йر���
	USH matchHead = 0;//ƥ��ͷ
	USH curMatchLength = 0;
	USH curMatchDist = 0;

	//�������йر���
	USH chFlag = 0;
	UCH bitCount = 0;
	bool IsLen = false;

	while (lookAhead){
		//1.�������������ַ������뵽��ϣ���У����õ�ƥ������ͷ
		_ht.Insert(matchHead, _pWin[start + 2], start , hashAddr);
		curMatchLength = 0;
		curMatchDist = 0;
		if (matchHead != 0){
			//2.��ȡ���ƥ��,��ȡ�����Ⱦ����
			curMatchLength=LongestMatch(matchHead, curMatchDist,start);
		}
		//3.�鿴�Ƿ��ҵ�ƥ��
		if (curMatchLength<MIN_MATCH){
			//δ�ҵ��ظ��ַ���
			//��startд��ѹ���ļ���
			fputc(_pWin[start], fOut);

			//д��ǰ�ַ���Ӧ�ı�ǣ���Դ�ַ���0���
			WriteFlag(fFlag, chFlag, bitCount, false);

			++start;
			lookAhead--;
		}else{
			//�ҵ�ƥ�䣬�����Ⱦ����д�뵽ѹ���ļ���
			fputc(curMatchLength-3, fOut);
			fwrite(&curMatchDist, sizeof(curMatchDist), 1, fOut);

			//д��ǰ�ַ���Ӧ�ı�ǣ����Ⱦ������1����
			WriteFlag(fFlag, chFlag, bitCount, true);

			//lookAhead�������л������е��ֽ���
			lookAhead -= curMatchLength;
			
			//���Ѿ�ƥ�䵽���ַ������뵽��ϣ����
			--curMatchLength;
			while (curMatchLength){
				start++;
				_ht.Insert(matchHead, _pWin[start+2], start, hashAddr);
				curMatchLength--;
			}
			start++;
		}
		//������л�������ʣ���ַ��ĸ���
		if (lookAhead <=MIN_LOOKAHEAD){
			//�������
			FillWindow(fIn, lookAhead,start);
		}

	}

	//ѭ���������п��ܻ���û��д�����ļ��е�����
	if (bitCount > 0 && bitCount < 8){
		chFlag <<= (8 - bitCount);
		fputc(chFlag, fFlag);
	}


	
	fclose(fFlag);
	fclose(fIn);

	MergeFile(fOut, FileSize);
	fclose(fOut);
}

USH LZ77::LongestMatch(USH matchHead, USH &curMatchDist, USH start){
	//���ڲ��һ������н���ƥ��
	USH curMatchLen = 0;//��ǰƥ�䳤��
	UCH maxMatchLen = 0;
	UCH maxMatchCount = 255;//����ƥ����������⻷״���ĳ���
	USH curMatchStart = 0;//��ǰƥ���ڲ��һ������ĵ���ʼλ��

	//limitԼ������ǰ��ƥ�����Զ����
	USH limit = start > MAX_DIST ? start - MAX_DIST : 0;

	//���л������е���ʼλ��
	UCH* pstart = _pWin + start;
	//���л������е���ֹλ��
	UCH *pend = pstart + MAX_MATCH;

	//���һ�����ƥ�䴮����ʼλ��
	UCH *pMatchStart = _pWin + matchHead;
	//std::cout << pMatchStart << std::endl;
	//��ʼƥ��
	do{
		
		curMatchLen = 0;
		//��ʼƥ��
		while (pstart < pend&&*pstart == *pMatchStart){
			curMatchLen++;
			pstart++;
			pMatchStart++;
		}
		//һ��ƥ�����
		if (curMatchLen > maxMatchLen){
			maxMatchLen = curMatchLen;
			curMatchStart = matchHead;
		}
	} while ((matchHead = _ht.GetNext(matchHead)) > limit && maxMatchCount--);


	curMatchDist = start - curMatchStart;
	return maxMatchLen;
}


void LZ77::MergeFile(FILE * fOut,  ULL fileSize){
	//��ѹ���ļ��ͱ���ļ����кϲ�
	//��ȡ�����Ϣ�ļ��е����ݣ�Ȼ��д��ѹ���ļ���
	FILE * fInF = fopen("Flag.txt", "rb");
	size_t flagSize = 0;
	UCH *pReadBuff = new UCH[1024];
	while (true){
		size_t rdSize = fread(pReadBuff, 1, 1024, fInF);
		if (rdSize == 0){
			break;
		}
		else{
			fwrite(pReadBuff, 1, rdSize, fOut);
			flagSize += rdSize;
		}
	}

	fwrite(&flagSize, sizeof(flagSize), 1, fOut);
	fwrite(&fileSize, sizeof(fileSize), 1, fOut);

	delete[] pReadBuff;
	fclose(fInF);
	//������ļ�ɾ��
}


//1.���Ҵ��������ݰ��Ƶ��󴰿�
//2.��ȡWSIZE��ѹ�����ݵ��Ҵ���
//3.���¹�ϣ��
void LZ77::FillWindow(FILE * fIn, int & lookAhead, USH &start){

	if (start >= WSIZE){
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		memset(_pWin + WSIZE, 0, WSIZE);
		start -= WSIZE;
		//���¹�ϣ��
		_ht.Update();

		if (!feof(fIn)){
			//��������ļ�ĩβ�������
			lookAhead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
		}
	}
}


//chFlag:����Դ�ַ����ǳ��Ⱦ����
//0����Դ�ַ���1�����Ⱦ����
//bitCount:����chFlag���Ѿ����ù��ı���λ
void LZ77::WriteFlag(FILE * fOut, USH &chFlag, UCH &bitCount, bool isLen){
	chFlag <<= 1;
	if (isLen){
		chFlag |= 1;
	}
	bitCount++;
	if (bitCount == 8){
		//�����д�����ļ���
		fputc(chFlag, fOut);
		chFlag = 0;
		bitCount = 0;
	}
}






void LZ77::UnCompressFile(const std::string & path){
	//��ѹ���ļ��ͱ���ļ�
	FILE * fInData = fopen(path.c_str(), "rb");
	if (fInData == nullptr){
		std::cout << "ѹ���ļ���ʧ��" << std::endl;
		return;
	}

	//����������ݵ��ļ�ָ��
	FILE * fInFlag = fopen(path.c_str(), "rb");
	if (fInFlag == nullptr){
		fclose(fInData);
		std::cout << "����ļ���ʧ��" << std::endl;
		return;
	}

	//��ȡԴ�ļ���С
	ULL fileSize = 0;
	fseek(fInFlag, 0 - sizeof(fileSize), SEEK_END);
	fread(&fileSize, sizeof(fileSize), 1, fInFlag);

	//��ȡ�����Ϣ�Ĵ�С��Դ�ļ��Ĵ�С
	int flagSize = 0;
	fseek(fInFlag,0-sizeof(fileSize)-sizeof(flagSize) , SEEK_END);
	fread(&flagSize, sizeof(flagSize), 1, fInFlag);

	//����ȡ�����Ϣ���ļ�ָ���ƶ������������ݵ���ʼλ��
	fseek(fInFlag, 0 - sizeof(flagSize)-sizeof(fileSize)-flagSize, SEEK_END);


	FILE * fOut = fopen("LZUnCompre.TXT", "wb");

	//�ٶ���һ���ļ�ָ��������ԭƥ�䴮
	FILE * fRe = fopen("LZUnCompre.TXT", "rb");

	assert(fOut);
	UCH bitCount = 0;
	UCH chFlag = 0;
	ULL encodeCount = 0;
	while (encodeCount<fileSize){
		if (bitCount == 0){
			//��ȡһ�����
			chFlag = fgetc(fInFlag);
			bitCount = 8;
		}
		
		//��⵱ǰ�ı����0����1
		if (chFlag & 0x80){
			//������Ϊ1��ʾ�Ǿ��볤�ȶ�
			USH matchLen = fgetc(fInData) + 3;
			USH matchDist = 0;
			fread(&matchDist, sizeof(matchDist), 1, fInData);

			//��ջ����������������е�����д�뵽�ļ���
			fflush(fOut);
			//�����Ѿ�����Ĵ�С����Ϊ�˳�ѭ��������
			encodeCount += matchLen;
			UCH ch;

			//��fReȥǰ���ж�ȡƥ�䴮������
			fseek(fRe, 0-matchDist, SEEK_END);
			while (matchLen){
				ch=fgetc(fRe);
				fputc(ch, fOut);
				matchLen--;
				fflush(fOut);
			}
		}
		else{
			//���Ϊ0�����ȡ������ԭ�ַ�
			UCH ch = fgetc(fInData);
			fputc(ch, fOut);
			encodeCount += 1;
		}
		chFlag <<= 1;
		bitCount--;
	}

	fclose(fInData);
	fclose(fInFlag);
	fclose(fOut);
	fclose(fRe);

}