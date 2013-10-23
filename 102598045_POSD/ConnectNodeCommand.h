#pragma once

#include "UnexecutableCommand.h"

class ConnectNodeCommand : public UnexecutableCommand{
	friend class IntegrationTest;
	FRIEND_TEST(IntegrationTest,testRedoConnectComponent);
	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest,testCommandManager);
	friend class ConnectNodeCommandTest;
	FRIEND_TEST(ConnectNodeCommandTest,testConnectNodeCommand);
	FRIEND_TEST(ConnectNodeCommandTest,testBackupConnector);
public:
	ConnectNodeCommand(Presentation* presentation);
	~ConnectNodeCommand();

	void setupCommand();

	void execute();
	void unExecute();
private:
	Component* firstNode;
	Component* secondNode;
	Component* connector;
	void backupConnector(Component* firstNode,Component* secondNode);
};