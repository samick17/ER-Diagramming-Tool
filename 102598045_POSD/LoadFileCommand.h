#pragma once

#include "Command.h"
#include <string>

class LoadFileCommand : public Command{
public:
	LoadFileCommand(Presentation* presentation);
	~LoadFileCommand();
	
	void setupCommand();

	void execute();
	void unExecute();
private:
	string filePath;
};