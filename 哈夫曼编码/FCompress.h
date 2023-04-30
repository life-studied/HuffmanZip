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
		string fileTxt;				//文件文本
		string hbin;				//二进制数据
		string OriFileSuffix;		//源文件后缀（如果是压缩的文件）
		ct table;					//存储码点的表
		short fillNum;				//最后的填充0数目
		fileInfo();
	};
	static string patTxt;
private:
	//工具成员
	file_manager fm;		//文件读写工具
	Haffman* HCode;			//编码工具
private:
	//文件数据
	fileInfo fInfo;
public:
	FCompress(const string& filename);	//构造函数
public:
	void process();				//开始压缩/解压
private:
	bool isCompressed;			//判断文件类型
private:
	void insertCT(const string& line);		//插入ct表项
};

