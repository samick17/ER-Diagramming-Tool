#pragma once

#include "Command.h"

class FindComponentCommand : public Command{
public:
	FindComponentCommand(Presentation* presentation);
	~FindComponentCommand();
	
	void setInfo(string info);

	void execute();
	void unExecute();
	Component* getComponent();
protected:
	Component* component;
	string info;
};