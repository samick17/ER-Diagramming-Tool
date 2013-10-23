#include "RedoCommand.h"
#include "CommandManager.h"

RedoCommand::RedoCommand(Presentation* presentation) : Command(presentation){	
}

RedoCommand::~RedoCommand(){
}
/**Non testable function**/
void RedoCommand::execute(){	
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->redo();
	this->presentation->logMessage("Redo succeed.",true);
	this->presentation->displayComponents();
	this->presentation->displayConnections();	
}