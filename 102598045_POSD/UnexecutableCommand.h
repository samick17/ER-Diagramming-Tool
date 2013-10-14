#pragma once

#include "Command.h"

class UnexecutableCommand : public Command{
public:
	UnexecutableCommand(Presentation* presentation);
	~UnexecutableCommand();

	string getCommandInformation();
	void setupCommand();

	bool isUnexecutable();

	void execute();
	void unExecute();
protected:
	bool getExecutionFlag();
private:
	bool executionFlag;//true execute, false unexecute
};