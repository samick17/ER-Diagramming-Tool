#pragma once

#include "UnexecutableCommand.h"

class ConnectNodeCommand : public UnexecutableCommand{
	friend class IntegrationTest;
	FRIEND_TEST(IntegrationTest,testRedoConnectComponent);
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