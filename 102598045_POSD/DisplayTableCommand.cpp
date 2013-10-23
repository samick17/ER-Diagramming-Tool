#include "DisplayTableCommand.h"

DisplayTableCommand::DisplayTableCommand(Presentation* presentation) : Command(presentation){	
}

DisplayTableCommand::~DisplayTableCommand(){
}
/**Non testable function**/
void DisplayTableCommand::execute(){
	this->presentation->displayTable();	
}