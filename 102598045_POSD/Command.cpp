#include "Command.h"
#include "ERModel.h"
#include "TextUI.h"

Command::Command(Presentation* presentation) : presentation(presentation){
	this->commandInformation = "";
}

Command::~Command(){
}

string Command::getCommandInformation(){
	return this->commandInformation;
}

void Command::setupCommand(){
}

bool Command::isUnexecutable(){
	return false;
}