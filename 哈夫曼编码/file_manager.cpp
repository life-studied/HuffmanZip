#include "file_manager.h"

file_manager::file_manager() {}

string file_manager::getData(const string& filename) throw(std::ifstream::failure)
{
	std::ifstream streamReader(filename, std::ios::binary);
	if (!streamReader.is_open())
		throw std::ifstream::failure("file couldn't open");
	streamReader.seekg(0, std::ios::end);		//游标移到文件结尾
	std::streamoff filesize = streamReader.tellg();		//获取游标当前位置 - 文件开始位置，此处为文件大小
	char* _data = new char[filesize+1];					//分配内存
	streamReader.seekg(0, std::ios::beg);		//跳转回开始
	streamReader.read(_data, filesize);		//读取文件
    _data[filesize] = '\0';
	streamReader.close();
	string data(_data);
	delete[] _data;
	return std::move(data);
}

void file_manager::writeData(const string& filename, const string& txt) throw(std::ofstream::failure)
{
    std::ofstream streamWriter(filename, std::ios::binary);
    if (!streamWriter.is_open())
        throw std::ofstream::failure("file couldn't open");
    const char* data = txt.c_str();
    size_t size = txt.size();
    streamWriter.write(data, size);
    streamWriter.close();
}

string& file_manager::replaceAll(string& context, const string& from, const string& to)
{
	size_t lookHere = 0;
	size_t foundHere;
	while ((foundHere = context.find(from, lookHere)) != string::npos)		// find from lookHere
	{																					// to avoid the string
		context.replace(foundHere, from.size(), to);					//"to" is the substr
		lookHere = foundHere + to.size();												// of "from"
	}
	return context;
}

vector<string> file_manager::parseFileToWords(const string& fileTxt)
{
    size_t foundHere_a = 0, foundHere_b = 0;
    string englishWord;
    for (char i = 'a'; i <= 'z'; i++)
        englishWord += i;
    for (char i = 'A'; i <= 'Z'; i++)
        englishWord += i;
    foundHere_a = fileTxt.find_first_not_of(englishWord);
    if (foundHere_a == string::npos)
        return std::move(vector<string>());
    vector<string> words;
    while ((foundHere_b = fileTxt.find_first_not_of(englishWord, foundHere_a + 1)) != string::npos)
    {
        if (foundHere_b == foundHere_a + 1)
        {
            foundHere_a = foundHere_b;
            continue;
        }
        words.push_back(fileTxt.substr(foundHere_a + 1, foundHere_b - foundHere_a - 1));
        foundHere_a = foundHere_b;
    }
    words.push_back(fileTxt.substr(foundHere_a + 1, fileTxt.size() - foundHere_a - 1));
    return words;
}
