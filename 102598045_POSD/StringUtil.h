#pragma once

#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

class StringUtil{
public:
	static string intToString(int number);
	static vector<string> split(const string &str,char delim);
	static string &trimStart(string &s);
	static string &trimEnd(string &s);
	static string &trim(string &s);	
	static string appendWithComma(vector<string> stringVector);
};