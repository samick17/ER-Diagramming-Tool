#include "ExitCommand.h"

ExitCommand::ExitCommand(Presentation* presentation) : Command(presentation){	
}

ExitCommand::~ExitCommand(){
}

void ExitCommand::execute(){
	this->presentation->close();
}