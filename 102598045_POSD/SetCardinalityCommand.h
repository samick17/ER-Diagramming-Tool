#pragma once

#include "Command.h"

class SetCardinalityCommand : public Command{
public:
	SetCardinalityCommand(Presentation* presentation,Component* firstNode,Component* secondNode);
	~SetCardinalityCommand();
	
	void execute();
	void unExecute();
private:
	Component* firstNode;
	Component* secondNode;
};