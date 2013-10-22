#include "DisplayDiagramCommand.h"
#include "StringSymbol.h"

DisplayDiagramCommand :: DisplayDiagramCommand(Presentation* presentation) : Command(presentation){	
}

DisplayDiagramCommand::~DisplayDiagramCommand(){
}
/**Non testable function**/
void DisplayDiagramCommand :: execute(){
	this->presentation->logMessage("The ER diagram is displayed as follows:",true);	
	this->presentation->displayComponents();	
	this->presentation->logMessage(StringSymbol::Empty,true);
	this->presentation->displayConnections();
}