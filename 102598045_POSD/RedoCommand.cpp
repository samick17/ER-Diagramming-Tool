#include "RedoCommand.h"
#include "CommandManager.h"

RedoCommand :: RedoCommand(Presentation* presentation) : Command(presentation){	
}

RedoCommand::~RedoCommand(){
}

void RedoCommand :: execute(){	
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->redo();
	this->presentation->displayComponents();
	this->presentation->displayConnections();	
}

void RedoCommand::unExecute(){
}