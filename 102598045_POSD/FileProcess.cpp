#include "FileProcess.h"
#include "StringUtil.h"
#include "CharSymbol.h"
#include "Exception.h"

FileProcess::FileProcess(string filePath){
    this->extractFileInfo(filePath);
}

FileProcess::~FileProcess(){
}

string FileProcess::getFileName(){
    return this->fileName;
}

string FileProcess::getFileExtension(){
    return this->fileExtension;
}

void FileProcess::extractFileInfo(string filePath){
    unsigned int lastIndex = StringUtil::lastIndexOf(filePath,CharSymbol::Dot);
    if(lastIndex == -1)
        throw Exception("Please enter correct format!");
    this->fileName = filePath.substr(0,lastIndex);
    this->fileExtension = filePath.substr(lastIndex);
}