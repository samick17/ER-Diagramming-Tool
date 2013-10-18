#pragma once

#include "UnexecutableCommand.h"
#include "ConnectionData.h"
#include "HashMap.h"

typedef pair<string,ConnectionData*> ConnectionDataPair;

class DeleteComponentCommand : public UnexecutableCommand{
public:
	DeleteComponentCommand(Presentation* presentation);
	~DeleteComponentCommand();

	void setupCommand();

	void execute();
	void unExecute();
private:
	Component* component;
	HashMap<string,Connector*> connectionSet;
	HashMap<string,ConnectionData*> connectionDataMap;
	void saveConnectionData(Connector* connector);
	void clearConnectionDataMap();
	void removeAndDisconnectComponents();
	void reConnectComponents(ConnectionData* connectionData,Connector* connector);
};