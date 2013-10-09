#pragma once

#include "UnexecutableCommand.h"

class ConnectNodeCommand : public UnexecutableCommand{
public:
	ConnectNodeCommand(Presentation* presentation);
	~ConnectNodeCommand();

	void execute();
	void unExecute();
private:
	Component* firstNode;
	Component* secondNode;
	Component* connector;
	void doConnectTwoNode();
	void backupConnectInfo(Component* firstNode,Component* secondNode);
};