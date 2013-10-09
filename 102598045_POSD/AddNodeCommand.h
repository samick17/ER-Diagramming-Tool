#pragma once

#include "UnexecutableCommand.h"

class AddNodeCommand : public UnexecutableCommand{
public:
	AddNodeCommand(Presentation* presentation);
	~AddNodeCommand();

	void execute();
	void unExecute();
private:
	Component* node;
	void doAddNode();
	Component* getNodeToAdd();
};