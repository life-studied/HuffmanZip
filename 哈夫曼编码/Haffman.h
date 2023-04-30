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
	//���ⲿʹ�õ��������ͽӿ�
	struct CodePoint	//����������Ա�ѹ�����ļ����洢��ÿ���ַ�ԭ���Haffman���ӳ���Ƶ��
	{
		char Ach;		//Ascii Code
		string Hch;		//Haffman Code
		int freq;
		CodePoint(char ach, string hch = "", int f = 0) :Ach(ach), Hch(hch), freq(f) {}
	};

	using CodePointTable = vector<CodePoint*>;	//�������ڹ�����������

private:
	//Ԥ����ṹ��������
	struct TreeNode		//���������Ľڵ㣨���ͣ�
	{
		TreeNode* left, *right;
		unsigned char ch;
		int freq;
		TreeNode(unsigned char ch, int f, TreeNode* _left = nullptr, TreeNode* _right = nullptr) :ch(ch), freq(f), left(_left), right(_right) {}
	};
		
	struct CodeTableItem	//����������ı�����ͣ�
	{
		string code;
		CodeTableItem(string c = ""): code(c){}
	};

	struct NodeFreqCmp	//�ڵ�Ƶ�αȽ���
	{
		bool operator()(const TreeNode* a, const TreeNode* b) { return a->freq > b->freq; }
	};

	using CodeTable = unordered_map<char, CodeTableItem>;						//�����γɵı���ӳ������ͣ�
	using FreqQue = priority_queue<TreeNode*, vector<TreeNode*>, NodeFreqCmp>;	//��ʱ�洢�ڵ�Ķ��У����ͣ�

	
private:
	//���Ա����
	string txt;						//Դ�ı�
	string bin;						//�������ı�
	CodePointTable baseTable;		//���������Ϣ��������ʱ�洢�ı�
	short fillNum;					//����ֶ�����
	CodeTable mappingTable;			//���յ�ӳ�������Դ�ַ���Haffman�����ƴ���ӳ��
	TreeNode* head;					//Haffman�������ڽ�ѹʱ����ӳ�䡣
public:
	Haffman(const string &txt);									//�����ı�����Haffman��������ѹ��Դ�ı�
	Haffman(const CodePointTable& table, const string& Hbin, short fillNum);	//������֪ct����Haffman�������ڽ�ѹ�������ı�
private:
	Haffman();		//ί�й��캯��
public:
	string compress();			//ѹ��
	string decompress();		//��ѹ
	CodePointTable getCT();		//��ȡct
	short getFillNum();			//��ȡ����ֶ�����
private:
	//ѹ�����
	void StaicFreq();			//ͳ���ַ����ֵ�Ƶ��
	void createTree();			//����baseTable������������
	void createMap();			//���ݹ�����������Ascii->HfmCodeӳ�䣬ͬʱ����ct
private:
	//��������
	void createMap(string bin, TreeNode* now);
	unsigned char StrToBin(const string& binStr);		//�������ַ���תuchar
};

