#include "Command.h"
#include "ERModel.h"
#include "TextUI.h"

Command::Command(Presentation* presentation) : presentation(presentation){
}

Command::~Command(){
}

string Command::getCommandInformation(){
	return "";
}

void Command::setupCommand(){
}

bool Command::isUnexecutable(){
	return false;
}