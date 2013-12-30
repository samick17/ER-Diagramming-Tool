#pragma once

#include <string>
#include <gtest/gtest_prod.h>

using namespace std;

class FileProcess{
    friend class FileProcessTest;
    FRIEND_TEST(FileProcessTest,testExtractFileInfo);
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