#include "DisplayDiagramCommand.h"
#include "StringSymbol.h"

DisplayDiagramCommand::DisplayDiagramCommand(Presentation* presentation) : Command(presentation){	
}

DisplayDiagramCommand::~DisplayDiagramCommand(){
}
/**Non testable function**/
void DisplayDiagramCommand::execute(){
	this->presentation->displayDiagram();
}