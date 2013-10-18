#pragma once

#include "Command.h"

class DisplayTableCommand : public Command{
public:
	DisplayTableCommand(Presentation* presentation);
	~DisplayTableCommand();

	void execute();
};