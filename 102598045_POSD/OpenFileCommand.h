#pragma once

#include "Command.h"
#include <string>

class OpenFileCommand : public Command{
public:
	OpenFileCommand(Presentation* presentation);
	~OpenFileCommand();	

	void execute();
private:
	string filePath;
};