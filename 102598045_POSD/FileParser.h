#pragma once

#include "Document.h"
#include "Component.h"
#include "ERModel.h"
#include "ConnectionData.h"
#include <hash_map>
#include <queue>

typedef pair<string,string> StringPair;

using namespace std;

class FileParser{
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
	bool isQueueArriveConnectionDataID(int index);
};