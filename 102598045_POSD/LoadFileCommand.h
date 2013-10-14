#pragma once

#include "Command.h"
#include "Document.h"
#include "Component.h"
#include "ConnectionData.h"
#include <hash_map>
#include <queue>

typedef pair<string,string> StringPair;

class LoadFileCommand : public Command{
public:
	LoadFileCommand(Presentation* presentation);
	~LoadFileCommand();
	
	void execute();
	void unExecute();

private:
	queue<StringPair> componentDataQueue;
	queue<ConnectionData> connectionDataQueue;
	void loadAllComponentsFromDoc(Document& doc);
	void loadAllConnectorsFromDoc(Document& doc);
	void loadAllPrimaryKeyFromDoc(Document& doc);
	void addAllComponentToERModel();
	void addConnector(ConnectionData connectionData,string connectionName);
	bool isQueueArriveConnectionDataID(int index);
};