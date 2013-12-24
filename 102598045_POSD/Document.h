#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "StringSymbol.h"
#include <gtest/gtest_prod.h>

using namespace std;

class Document{
    friend class InputFileParserTest;
    FRIEND_TEST(InputFileParserTest,testLoadAllConnectorsFromDoc);
    FRIEND_TEST(InputFileParserTest,testLoadAllPrimaryKeyAndSetUpFromDoc);
    friend class DocumentTest;
    FRIEND_TEST(DocumentTest,testDocument);
public:
    Document(string fileName,string fileExtension = StringSymbol::Empty);
    ~Document();

    void openFile();
    void saveFile();
    void writeLine(string line);
    string readLine();
protected:
    virtual void doSaveFile();
    string fileName,fileExtension;
private:
    string filePath;
    ifstream inputStream;
    ofstream outputStream;
    unsigned int readIndex;
    vector<string> rwBuffer;
};