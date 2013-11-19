#include "Command.h"
#include "ERModel.h"
#include "TextUI.h"
#include "StringSymbol.h"

Command::Command(){
    this->executionFlag = false;
}

Command::~Command(){
    if(this->executionFlag)
        this->onExecuteDestroy();
    else
        this->onUnExecuteDestroy();
}

void Command::onExecuteDestroy(){
}

void Command::onUnExecuteDestroy(){
}

void Command::execute(){
    if(this->executionFlag)
        return;
    this->doExecute();
    this->executionFlag = true;
}

void Command::unExecute(){
    if(!this->executionFlag)
        return;
    this->doUnExecute();
    this->executionFlag = false;
}