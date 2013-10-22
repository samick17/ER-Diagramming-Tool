#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <gtest/gtest_prod.h>

using namespace std;

class Document{
	friend class FileParserTest;
	FRIEND_TEST(FileParserTest,testLoadAllConnectorsFromDoc);
	FRIEND_TEST(FileParserTest,testLoadAllPrimaryKeyAndSetUpFromDoc);
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