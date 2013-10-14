#pragma once

#include "UnexecutableCommand.h"

class ConnectNodeCommand : public UnexecutableCommand{
public:
	ConnectNodeCommand(Presentation* presentation);
	~ConnectNodeCommand();

	string getCommandInformation();
	void setupCommand();

	void execute();
	void unExecute();
private:
	Component* firstNode;
	Component* secondNode;
	Component* connector;	
	void backupConnector(Component* firstNode,Component* secondNode);
};