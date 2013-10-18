#pragma once

#include "FindComponentCommand.h"

class FindEntityCommand : public FindComponentCommand{
public:
	FindEntityCommand(Presentation* presentation);
	~FindEntityCommand();
	
	void execute();
};