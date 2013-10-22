#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <gtest/gtest_prod.h>

using namespace std;

class Document{
	friend class InputFileParserTest;
	FRIEND_TEST(InputFileParserTest,testLoadAllConnectorsFromDoc);
	FRIEND_TEST(InputFileParserTest,testLoadAllPrimaryKeyAndSetUpFromDoc);
	friend class OutputFileParserTest;
	FRIEND_TEST(OutputFileParserTest,testWriteAllComponentsToDoc);
	FRIEND_TEST(OutputFileParserTest,testWriteAllConnectorsToDoc);
	FRIEND_TEST(OutputFileParserTest,testWriteAllPrimaryKeyToDoc);
	friend class DocumentTest;	
	FRIEND_TEST(DocumentTest,testDocument);
public:
	Document(string filePath);
	~Document();

	void openFile();
	void saveFile();
	void wirteLine(string line);
	string readLine();
private:	
	string filePath;
	ifstream inputStream;
	ofstream outputStream;
	unsigned int readIndex;
	vector<string> rwBuffer;
};