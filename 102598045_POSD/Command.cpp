#include "Command.h"
#include "ERModel.h"
#include "TextUI.h"

Command::Command(Presentation* presentation) : presentation(presentation){
}

Command::~Command(){
}

bool Command::isUnexecutable(){
	return false;
}