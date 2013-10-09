#pragma once

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Document{
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