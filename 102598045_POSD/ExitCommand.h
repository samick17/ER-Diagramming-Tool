#pragma once

#include "Command.h"

class ExitCommand : public Command{
public:
	ExitCommand(Presentation* presentation);
	~ExitCommand();

	void execute();
};