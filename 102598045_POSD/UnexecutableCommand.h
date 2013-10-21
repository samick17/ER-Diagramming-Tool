#pragma once

#include "Command.h"

class UnexecutableCommand : public Command{
public:
	UnexecutableCommand(Presentation* presentation);
	~UnexecutableCommand();

	virtual void setupCommand() = 0;
	bool isUnexecutable();

	void execute();
	virtual void unExecute();
protected:
	bool getExecutionFlag();
private:
	bool executionFlag;//true execute, false unexecute
};