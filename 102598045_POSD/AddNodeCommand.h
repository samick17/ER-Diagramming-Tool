#pragma once

#include "UnexecutableCommand.h"

class AddNodeCommand : public UnexecutableCommand{
public:
	AddNodeCommand(Presentation* presentation);
	~AddNodeCommand();

	void setupCommand();

	void execute();
	void unExecute();
private:	
	Component* node;
	Component* getNodeToAdd();
};