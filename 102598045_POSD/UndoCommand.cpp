#include "UndoCommand.h"
#include "CommandManager.h"

UndoCommand :: UndoCommand(Presentation* presentation) : Command(presentation){	
}

UndoCommand::~UndoCommand(){
}
/**Non testable function**/
void UndoCommand :: execute(){
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->undo();
	this->presentation->logMessage("Undo succeed.",true);
	this->presentation->displayComponents();
	this->presentation->displayConnections();
}