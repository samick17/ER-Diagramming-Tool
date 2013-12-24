#pragma once

#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

class StringUtil{
public:
    static string intToString(int number);
    static vector<string> split(const string &str,char delim);
    static string &trimStart(string &str);
    static string &trimEnd(string &str);
    static string &trim(string &str);
    static unsigned int lastIndexOf(string &str,char delim);
    static string appendWithComma(vector<string> stringVector);
};