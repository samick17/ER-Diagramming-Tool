#include "UndoCommand.h"
#include "CommandManager.h"

UndoCommand :: UndoCommand(Presentation* presentation) : Command(presentation){	
}

UndoCommand::~UndoCommand(){
}

void UndoCommand :: execute(){
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->undo();
	this->presentation->displayComponents();
	this->presentation->displayConnections();
}

void UndoCommand::unExecute(){
}