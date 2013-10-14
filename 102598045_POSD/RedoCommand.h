#pragma once

#include "Command.h"

class RedoCommand : public Command{
public:
	RedoCommand(Presentation* presentation);
	~RedoCommand();
	
	void execute();
	void unExecute();
};