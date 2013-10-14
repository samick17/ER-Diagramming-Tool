#pragma once

#include <string>
#include "Component.h"
#include "Presentation.h"

using namespace std;

class Presentation;
class TextUI;
class ERModel;

class Command{
public:	
	Command(Presentation* presentation);
	virtual ~Command();
	
	string getCommandInformation();
	virtual void setupCommand();

	virtual bool isUnexecutable();
		
	virtual void execute() = 0;	
	virtual void unExecute() = 0;
protected:
	Presentation* presentation;
	string commandInformation;
};