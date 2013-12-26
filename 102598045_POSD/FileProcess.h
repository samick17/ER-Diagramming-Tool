#pragma once

#include <string>

using namespace std;

class FileProcess{
public:
    FileProcess(string filePath);
    virtual ~FileProcess();
protected:
    string getFileName();
    string getFileExtension();
private:
    void extractFileInfo(string filePath);
    string fileName,fileExtension;
};