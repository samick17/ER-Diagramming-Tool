#pragma once

#include "UnexecutableCommand.h"
#include "ConnectionData.h"
#include <hash_map>

typedef pair<string,ConnectionData*> ConnectionDataPair;

class DeleteComponentCommand : public UnexecutableCommand{
public:
	DeleteComponentCommand(Presentation* presentation);
	~DeleteComponentCommand();

	void execute();
	void unExecute();
private:
	bool connectorFlag;
	Component* component;
	set<Connector*> connectionSet;
	hash_map<string,ConnectionData*> connectionDataMap;
	void clearConnectionDataMap();
	void doDeleteComponent();	
	void removeAndDisconnectComponents();
	void reConnectComponents(ConnectionData* connectionData,Connector* connector);
};