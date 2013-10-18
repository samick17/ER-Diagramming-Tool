#pragma once

#include "Command.h"

class DisplayDiagramCommand : public Command{
public:
	DisplayDiagramCommand(Presentation* presentation);
	~DisplayDiagramCommand();

	void execute();
};