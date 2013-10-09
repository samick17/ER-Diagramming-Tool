#pragma once

#include <vector>
#include <set>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

class StringUtil{
public:
	static string intToString(int number);
	static vector<string> split(const string &str,char delim);
	static string &trimStart(string &s);
	static string &trimEnd(string &s);
	static string &trim(string &s);	
	static string appendWithComma(set<string> stringSet);
private:
	static vector<string> &split(const string &str,char delim,vector<string> &elems);
};
