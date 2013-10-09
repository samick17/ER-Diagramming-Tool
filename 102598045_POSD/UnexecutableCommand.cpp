#include "UnexecutableCommand.h"

UnexecutableCommand :: UnexecutableCommand(Presentation* presentation) : Command(presentation){	
	this->executionFlag = false;
}

UnexecutableCommand::~UnexecutableCommand(){
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