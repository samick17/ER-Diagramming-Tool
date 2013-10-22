#include "StringUtil.h"
#include <sstream>
#include "StringSymbol.h"

//convert int to string
string StringUtil::intToString(int number){
	stringstream strStream; 
	strStream << number;    
	string str = strStream.str();
	return str;
}
//split string with char
vector<string> StringUtil::split(const string &str,char delim){
    vector<string> elements;  
	stringstream strStream(str);
    string line;
    while (getline(strStream,line,delim))
		elements.push_back(line);
    return elements;
}
//trim start
string &StringUtil::trimStart(std::string &str){
	str.erase(str.begin(),find_if(str.begin(),str.end(),not1(ptr_fun<int,int>(isspace))));
	return str;
}
//trim end
string &StringUtil::trimEnd(std::string &str){
	str.erase(find_if(str.rbegin(),str.rend(),not1(ptr_fun<int,int>(isspace))).base(),str.end());
	return str;
}
//trim start & end
string &StringUtil::trim(std::string &str){
	return trimStart(trimEnd(str));
}
//e.g. convert "a b c" to "a,b,c"
string StringUtil::appendWithComma(set<string> stringSet){
	string result;
	for each(string str in stringSet){
		result += str;	
		if(str != *(--stringSet.end()))
			result += StringSymbol::Comma;
	}
	return result;
}