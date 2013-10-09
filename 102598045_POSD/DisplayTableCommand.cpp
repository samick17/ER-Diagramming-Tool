#include "DisplayTableCommand.h"

DisplayTableCommand :: DisplayTableCommand(Presentation* presentation) : Command(presentation){	
}

DisplayTableCommand::~DisplayTableCommand(){
}

void DisplayTableCommand :: execute(){
	this->presentation->displayTable();	
}

void DisplayTableCommand::unExecute(){
}