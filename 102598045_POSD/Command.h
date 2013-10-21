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

	virtual bool isUnexecutable();
		
	virtual void execute() = 0;
protected:
	Presentation* presentation;
	string commandInformation;
};