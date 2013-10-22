#include "UnexecutableCommand.h"
#include "StringSymbol.h"

UnexecutableCommand :: UnexecutableCommand(Presentation* presentation) : Command(presentation){	
	this->executionFlag = false;
	this->commandInformation = StringSymbol::Empty;
}

UnexecutableCommand::~UnexecutableCommand(){
}

void UnexecutableCommand::setupCommand(){
}

bool UnexecutableCommand::isUnexecutable(){
	return true;
}

void UnexecutableCommand :: execute(){
	this->executionFlag = true;
}

void UnexecutableCommand::unExecute(){
	this->executionFlag = false;
}

bool UnexecutableCommand::getExecutionFlag(){
	return this->executionFlag;
}