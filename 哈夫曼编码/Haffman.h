#pragma once
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using std::string;
using std::unordered_map;
using std::priority_queue;
using std::vector;

class Haffman
{
public:
	//给外部使用的数据类型接口
	struct CodePoint	//码点数据来自被压缩的文件。存储了每个字符原码和Haffman码的映射和频次
	{
		char Ach;		//Ascii Code
		string Hch;		//Haffman Code
		int freq;
		CodePoint(char ach, string hch = "", int f = 0) :Ach(ach), Hch(hch), freq(f) {}
	};

	using CodePointTable = vector<CodePoint*>;	//码点表，用于构建哈夫曼表

private:
	//预定义结构体与声明
	struct TreeNode		//哈夫曼树的节点（类型）
	{
		TreeNode* left, *right;
		unsigned char ch;
		int freq;
		TreeNode(unsigned char ch, int f, TreeNode* _left = nullptr, TreeNode* _right = nullptr) :ch(ch), freq(f), left(_left), right(_right) {}
	};
		
	struct CodeTableItem	//哈夫曼编码的表项（类型）
	{
		string code;
		CodeTableItem(string c = ""): code(c){}
	};

	struct NodeFreqCmp	//节点频次比较器
	{
		bool operator()(const TreeNode* a, const TreeNode* b) { return a->freq > b->freq; }
	};

	using CodeTable = unordered_map<char, CodeTableItem>;						//最终形成的编码映射表（类型）
	using FreqQue = priority_queue<TreeNode*, vector<TreeNode*>, NodeFreqCmp>;	//临时存储节点的队列（类型）

	
private:
	//类成员数据
	string txt;						//源文本
	string bin;						//二进制文本
	CodePointTable baseTable;		//基础码点信息，用于临时存储的表
	short fillNum;					//填充字段数量
	CodeTable mappingTable;			//最终的映射表，用于源字符到Haffman二进制串的映射
	TreeNode* head;					//Haffman树，用于解压时反向映射。
public:
	Haffman(const string &txt);									//根据文本构建Haffman树，用于压缩源文本
	Haffman(const CodePointTable& table, const string& Hbin, short fillNum);	//根据已知ct构建Haffman树，用于解压二进制文本
private:
	Haffman();		//委托构造函数
public:
	string compress();			//压缩
	string decompress();		//解压
	CodePointTable getCT();		//获取ct
	short getFillNum();			//获取填充字段数量
private:
	//压缩组件
	void StaicFreq();			//统计字符出现的频次
	void createTree();			//根据baseTable创建哈夫曼树
	void createMap();			//根据哈夫曼树创建Ascii->HfmCode映射，同时创建ct
private:
	//辅助函数
	void createMap(string bin, TreeNode* now);
	unsigned char StrToBin(const string& binStr);		//二进制字符串转uchar
};

