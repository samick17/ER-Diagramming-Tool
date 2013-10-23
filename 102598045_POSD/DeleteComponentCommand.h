#pragma once

#include "UnexecutableCommand.h"
#include "ConnectionData.h"
#include "HashMap.h"

class DeleteComponentCommand : public UnexecutableCommand{
	friend IntegrationTest;
	FRIEND_TEST(IntegrationTest,testUndoDeleteComponent);
	FRIEND_TEST(IntegrationTest,testCommonUsage);
	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest,testCommandManager);
	friend class DeleteComponentCommandTest;
	FRIEND_TEST(DeleteComponentCommandTest,testDeleteComponentCommand);	
	FRIEND_TEST(DeleteComponentCommandTest,testSaveConnectionData);
	FRIEND_TEST(DeleteComponentCommandTest,testClearConnectionDataMap);
	FRIEND_TEST(DeleteComponentCommandTest,testRemoveAndDisconnectComponents);	
	FRIEND_TEST(DeleteComponentCommandTest,testReConnectComponents);
public:
	DeleteComponentCommand(Presentation* presentation);
	~DeleteComponentCommand();

	void setupCommand();

	void execute();
	void unExecute();
private:
	Component* component;
	HashMap<string,Connector*> connectionMap;
	HashMap<string,ConnectionData*> connectionDataMap;
	HashMap<string,unsigned int> componentIndexMap;
	void saveConnectionData(Connector* connector);
	void clearConnectionDataMap();
	void removeAndDisconnectComponents();
	void reConnectComponents(ConnectionData* connectionData,Connector* connector);
};