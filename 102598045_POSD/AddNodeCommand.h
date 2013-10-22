#pragma once

#include "UnexecutableCommand.h"

class AddNodeCommand : public UnexecutableCommand{
	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest,testCommandManager);
	friend class AddNodeCommandTest;
	FRIEND_TEST(AddNodeCommandTest,testAddNodeCommand);
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