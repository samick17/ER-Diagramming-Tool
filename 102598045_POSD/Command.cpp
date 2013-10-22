#include "Command.h"
#include "ERModel.h"
#include "TextUI.h"
#include "StringSymbol.h"

Command::Command(Presentation* presentation) : presentation(presentation){
	this->commandInformation = StringSymbol::Empty;
}

Command::~Command(){
}

string Command::getCommandInformation(){
	return this->commandInformation;
}

bool Command::isUnexecutable(){
	return false;
}