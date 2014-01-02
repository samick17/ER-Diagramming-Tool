#include "FileProcess.h"
#include "StringUtil.h"
#include "CharSymbol.h"
#include "Exception.h"

FileProcess::FileProcess(string filePath){
    pair<string,string> fileInfoPair = this->extractFileInfo(filePath);
    this->fileName = fileInfoPair.first;
    this->fileExtension = fileInfoPair.second;
}

FileProcess::~FileProcess(){
}

string FileProcess::getFileName(){
    return this->fileName;
}

string FileProcess::getFileExtension(){
    return this->fileExtension;
}

pair<string,string> FileProcess::extractFileInfo(string filePath){
    unsigned int lastIndex = StringUtil::lastIndexOf(filePath,CharSymbol::Dot);
    if(lastIndex == -1)
        throw Exception("Please enter correct format!");
    string fileName = filePath.substr(0,lastIndex);
    string fileExtension = filePath.substr(lastIndex);
    pair<string,string> fileInfoPair(fileName,fileExtension);
    return fileInfoPair;
}