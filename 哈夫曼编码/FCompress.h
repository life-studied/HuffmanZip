#pragma once
#include "file_manager.h"
#include "Haffman.h"
class FCompress
{
private:
	using ct = Haffman::CodePointTable;
	struct fileInfo
	{
		bool isCompressed;
		string fileTxt;				//�ļ��ı�
		string hbin;				//����������
		string OriFileSuffix;		//Դ�ļ���׺�������ѹ�����ļ���
		ct table;					//�洢���ı�
		short fillNum;				//�������0��Ŀ
		fileInfo();
	};
	static string patTxt;
private:
	//���߳�Ա
	file_manager fm;		//�ļ���д����
	Haffman* HCode;			//���빤��
private:
	//�ļ�����
	fileInfo fInfo;
public:
	FCompress(const string& filename);	//���캯��
public:
	void process();				//��ʼѹ��/��ѹ
private:
	bool isCompressed;			//�ж��ļ�����
private:
	void insertCT(const string& line);		//����ct����
};

