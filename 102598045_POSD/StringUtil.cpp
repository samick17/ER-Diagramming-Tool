#include "StringUtil.h"
#include <sstream>
#include "StringSymbol.h"
#include "Exception.h"

//convert int to string
string StringUtil::intToString(int number){
    stringstream stringStream;
    stringStream<<number;
    return stringStream.str();
}

int StringUtil::stringToInt(string str){
    int covertedInt;
    stringstream stringStream;
    stringStream.str(str);
    stringStream>>covertedInt;
    if(stringStream.fail())
        throw Exception("can not convert to int");
    return covertedInt;
}

string StringUtil::doubleToString(double number){
    ostringstream stringStream;
    stringStream<<number;
    return stringStream.str();
}
//split string with char
vector<string> StringUtil::split(const string &str,char delim){
    vector<string> elements;
    stringstream stringStream(str);
    string line;
    while (getline(stringStream,line,delim))
        elements.push_back(line);
    return elements;
}
//trim start
string &StringUtil::trimStart(string &str){
    str.erase(str.begin(),find_if(str.begin(),str.end(),not1(ptr_fun<int,int>(isspace))));
    return str;
}
//trim end
string &StringUtil::trimEnd(string &str){
    str.erase(find_if(str.rbegin(),str.rend(),not1(ptr_fun<int,int>(isspace))).base(),str.end());
    return str;
}
//trim start & end
string &StringUtil::trim(string &str){
    return trimStart(trimEnd(str));
}

unsigned int StringUtil::lastIndexOf(string &str,char delim){
    unsigned int index = -1;

    unsigned int count = 0;
    for each(char character in str){
        if(character == delim)
            index = count;
        count++;
    }

    return index;
}
//e.g. convert "a b c" to "a,b,c"
string StringUtil::appendWithComma(vector<string> stringVector){
    string result = StringSymbol::Empty;
    for each(string str in stringVector){
        if(str == StringSymbol::Empty)
            continue;
        result += str + StringSymbol::Comma;
    }
    result = result.substr(0,result.length()-1);
    return result;
}