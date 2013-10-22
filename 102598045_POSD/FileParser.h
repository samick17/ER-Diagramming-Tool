#pragma once

#include "Document.h"
#include "Component.h"
#include "ERModel.h"
#include "ConnectionData.h"
#include <queue>

using namespace std;

typedef pair<string,string> StringPair;

class FileParser{
	friend class FileParserTest;
	FRIEND_TEST(FileParserTest,testLoadAllComponentsFromDoc);
public:
	FileParser();
	~FileParser();

	void parseFileToModel(string filePath,ERModel* erModel);
private:
	ERModel* erModel;

	queue<StringPair> componentDataQueue;
	queue<ConnectionData> connectionDataQueue;

	void loadAllComponentsFromDoc(Document& document);
	void loadAllConnectorsFromDoc(Document& document);
	void loadAllPrimaryKeyAndSetUpFromDoc(Document& document);
	void addAllComponentToERModel();
	void addConnector(ConnectionData connectionData,string connectionName);
	bool isQueueArriveConnectionDataID(int id);
};