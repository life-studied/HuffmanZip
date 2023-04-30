#include "Haffman.h"
#include <stdexcept>
Haffman::Haffman(const string& txt) : Haffman()
{
	this->txt = txt;
	for (int i = 0; i < 256; i++)
		baseTable[i] = new CodePoint(i);
}

Haffman::Haffman(const CodePointTable& table, const string& Hbin, short fillNum = 0) : Haffman()
{
	this->bin = Hbin;
	this->baseTable = table;
	this->fillNum = fillNum;
}

Haffman::Haffman() : txt(""), bin(""), baseTable(CodePointTable(256, nullptr)), mappingTable(), head(nullptr), fillNum(0) {}

string Haffman::compress()
{
	StaicFreq();
	createTree();
	createMap();
	string binStr{};
	for (const auto& ch : txt)
	{
		binStr += mappingTable[ch].code;
		if (binStr.size() >= 8)
		{
			unsigned char ch = StrToBin(binStr.substr(0, 8));
			bin += ch;
			binStr.erase(0, 8);
		}
	}
	unsigned char ch = StrToBin(binStr.substr(0, 8));
	bin += ch;
	fillNum = 8 - short(binStr.size());
	return bin;
}

string Haffman::decompress()
{
	return string();
}

Haffman::CodePointTable Haffman::getCT()
{
	return baseTable;
}

short Haffman::getFillNum()
{
	return fillNum;
}

void Haffman::StaicFreq()
{
	for (const auto& ch : txt)
	{
		baseTable[(unsigned char)ch]->freq++;
	}
}

void Haffman::createTree()
{
	FreqQue que;
	for (const auto& codePoint : baseTable)
		que.push(new TreeNode(codePoint->Ach, codePoint->freq));
	while (que.size() > 1)
	{
		TreeNode* left = que.top(); que.pop();		//获取左右节点
		TreeNode* right = que.top(); que.pop();

		TreeNode* f = new TreeNode(0, left->freq + right->freq, left, right);
		que.push(f);
	}
	head = que.top();
}

void Haffman::createMap()
{
	if (!head)
		return;
	if (!head->left && !head->right)		//根节点就是叶子节点
	{
		mappingTable[head->ch] = CodeTableItem("0");
		return;
	}
	if(head->left)
			createMap("0", head->left);
	if(head->right)
		createMap("1", head->right);
}

void Haffman::createMap(string bin, TreeNode* now)
{
	if (!now->left && !now->right)
	{
		mappingTable[now->ch] = CodeTableItem(bin);
		baseTable[now->ch]->Hch = bin;
		return;
	}
	if (now->left)
		createMap(bin + "0", now->left);
	if (now->right)
		createMap(bin + "1", now->right);
}

unsigned char Haffman::StrToBin(const string& binStr)
{
	if (binStr.size() > 8)
		throw std::invalid_argument("string to bin: size > 8");
	unsigned char binaryCh{};
	size_t size = binStr.size();
	for (int i = 0; i < size; i++)
	{
		binaryCh += binStr[size - i - 1] - '0';
		binaryCh <<= 1;
	}
	for (int i = 0; i < 8 - size; i++)
		binaryCh <<= 1;
	return binaryCh;
}
