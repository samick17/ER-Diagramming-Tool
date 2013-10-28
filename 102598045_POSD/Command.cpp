#include "Command.h"
#include "ERModel.h"
#include "TextUI.h"
#include "StringSymbol.h"

Command::Command(){
	this->executionFlag = false;
}

Command::~Command(){
}