#pragma once

#include "UnexecutableCommand.h"
#include "ConnectionData.h"
#include <hash_map>

typedef pair<string,ConnectionData*> ConnectionDataPair;

class DeleteComponentCommand : public UnexecutableCommand{
public:
	DeleteComponentCommand(Presentation* presentation);
	~DeleteComponentCommand();

	string getCommandInformation();
	void setupCommand();

	void execute();
	void unExecute();
private:
	Component* component;
	set<Connector*> connectionSet;
	hash_map<string,ConnectionData*> connectionDataMap;
	void saveConnectionData(Connector* connector);
	void clearConnectionDataMap();
	void removeAndDisconnectComponents();
	void reConnectComponents(ConnectionData* connectionData,Connector* connector);
};