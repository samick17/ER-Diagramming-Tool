#include "UnexecutableCommand.h"
#include "StringSymbol.h"

UnexecutableCommand::UnexecutableCommand() : Command(){
    this->executionFlag = false;
    this->commandInformation = StringSymbol::Empty;
}

UnexecutableCommand::~UnexecutableCommand(){
}


bool UnexecutableCommand::isUnexecutable(){
    return true;
}

void UnexecutableCommand::execute(){
    this->executionFlag = true;
}

void UnexecutableCommand::unExecute(){
    this->executionFlag = false;
}

bool UnexecutableCommand::getExecutionFlag(){
    return this->executionFlag;
}