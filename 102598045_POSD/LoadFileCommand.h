#pragma once

#include "Command.h"
#include <string>

class LoadFileCommand : public Command{
public:
	LoadFileCommand(Presentation* presentation);
	~LoadFileCommand();
	
	void setupCommand();

	void execute();
private:
	string filePath;
};