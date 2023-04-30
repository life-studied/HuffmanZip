#include "FCompress.h"
#include <sstream>
#include <iostream>
string FCompress::patTxt = "HfmEncoding";

FCompress::FCompress(const string& filename)
{
	fInfo.fileTxt = fm.getData(filename);
	size_t pos = fInfo.fileTxt.find("\n");
	string line = fInfo.fileTxt.substr(0, pos);
	if (line == patTxt)
		isCompressed = true;
	else
		isCompressed = false;

	if (isCompressed)		//�ļ�Ϊѹ��״̬��
	{
		//��ȡ����ֶ�����
		size_t pos_n = fInfo.fileTxt.find("\n");
		line = fInfo.fileTxt.substr(pos + 1, pos_n - pos);
		fInfo.fillNum = line[0] - '0';
		//��ȡct��
		for (int i = 0; i < 256; i++)
		{
			pos_n = fInfo.fileTxt.find("\n", pos + 1);
			line = fInfo.fileTxt.substr(pos + 1, pos_n - pos);
			insertCT(line);
			pos = pos_n;
		}
		//��ȡʣ��������ı�
		fInfo.hbin = fInfo.fileTxt.substr(pos + 1);
		//����Haffman����
		HCode = new Haffman(fInfo.table, fInfo.hbin, fInfo.fillNum);
	}
	else
		HCode = new Haffman(fInfo.fileTxt);
}

void FCompress::process()
{
	if (isCompressed)
	{
		fInfo.fileTxt = HCode->decompress();
		fm.writeData("test2.txt", fInfo.fileTxt);
	}
	else
	{
		fInfo.hbin = HCode->compress();		//ѹ��
		fInfo.table = HCode->getCT();		//��ȡѹ�����ct��
		fInfo.fillNum = HCode->getFillNum();
		fInfo.fileTxt = patTxt + "\n";		//д��ѹ�������ַ���
		fInfo.fileTxt += (fInfo.fillNum) + '0'; fInfo.fileTxt += '\n';		//д������ֶ�����
		for (const auto& item : fInfo.table)
		{
			fInfo.fileTxt += std::to_string((unsigned char)item->Ach);
			fInfo.fileTxt += ' ';
			fInfo.fileTxt += item->Hch;
			fInfo.fileTxt += ' ';
			fInfo.fileTxt += std::to_string(item->freq) + '\n';
		}
		fInfo.fileTxt += fInfo.hbin;
		fm.writeData("test.hfm", fInfo.fileTxt);
		//fm.writeData(fInfo.OriFileSuffix, fInfo.fileTxt);
	}
		
}

void FCompress::insertCT(const string& line)
{
	int ach{}, f{};
	string hch;
	std::stringstream ss(line);
	ss >> ach;
	ss >> hch;
	ss >> f;
	fInfo.table[ach]->Ach = (char)ach;
	fInfo.table[ach]->Hch = hch;
	fInfo.table[ach]->freq = f;
}

FCompress::fileInfo::fileInfo() :isCompressed(true), fillNum(0), fileTxt(""), hbin(""), table(ct(256))
{
	for (int i = 0; i < 256; i++)
		table[i] = new Haffman::CodePoint(i);
}
