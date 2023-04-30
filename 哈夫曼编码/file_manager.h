#pragma once
#include <string>
#include <vector>
#include <fstream>
using std::string;
using std::vector;
class file_manager
{
public:
	file_manager();
	string getData(const string &filename) throw(std::ifstream::failure);
	void writeData(const string& filename, const string& txt) throw(std::ofstream::failure);
	string& replaceAll(
		string& context,
		const string& from,
		const string& to);
	vector<string> parseFileToWords(const string& fileTxt);
};

