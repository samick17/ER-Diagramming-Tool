#pragma once

#include "Command.h"

class UndoCommand : public Command{
public:
	UndoCommand(Presentation* presentation);
	~UndoCommand();

	void execute();
	void unExecute();
};