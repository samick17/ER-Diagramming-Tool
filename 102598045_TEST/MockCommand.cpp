#include "MockCommand.h"

MockCommand::MockCommand(){
    this->executionValue = 0;
}

MockCommand::~MockCommand(){
}

void MockCommand::doExecute(){
    this->executionValue++;
}

void MockCommand::doUnExecute(){
    this->executionValue--;
}

int MockCommand::getExecutionValue(){
    return this->executionValue;
}