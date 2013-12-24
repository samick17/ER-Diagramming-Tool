#include "Document.h"
#include "FileNotFoundException.h"
#include "StringSymbol.h"
#include "StringUtil.h"
#include "CharSymbol.h"

Document::Document(string fileName,string fileExtension) : fileName(fileName),fileExtension(fileExtension){
    this->readIndex = 0;
    this->filePath = this->fileName+this->fileExtension;
}

Document::~Document(){
    if(this->inputStream.is_open())
        this->inputStream.close();
    
    if(this->outputStream.is_open())
        this->outputStream.close();
}
//open file and  read all text to buffer
void Document::openFile(){
    this->inputStream = ifstream(this->filePath);
    //doesn't has such file on path
    if(!this->inputStream.good())
        throw FileNotFoundException();
    if(this->inputStream.is_open()){
        string line;
        while(getline(this->inputStream,line))
            this->rwBuffer.push_back(line);
        
        this->inputStream.close();
    }
}
//write all text from buffer, and save file
void Document::saveFile(){
    this->doSaveFile();

    this->outputStream = ofstream(this->filePath);

    vector<string> dataToWrite = this->rwBuffer;
    if(this->outputStream.is_open()){
        while(!dataToWrite.empty()){
            this->outputStream<<*dataToWrite.begin();
            dataToWrite.erase(dataToWrite.begin());
        }
        this->outputStream.close();
    }
}
//write line to buffer
void Document::writeLine(string line){
    this->rwBuffer.push_back(line+StringSymbol::NextLine);
}
//read line from buffer and return
string Document::readLine(){
    string line = StringSymbol::Empty;
    if(readIndex < this->rwBuffer.size()){
        line = *(this->rwBuffer.begin()+readIndex);
        readIndex++;
    }
    return line;
}

void Document::doSaveFile(){
}