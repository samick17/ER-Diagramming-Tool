#include "CommandManager.h"
#include "StackUtil.h"
#include "Exception.h"

using namespace std;

CommandManager::CommandManager(Presentation* presentation) : presentation(presentation){
}

CommandManager::~CommandManager(){	
	this->popAllStack();
}

Presentation* CommandManager::getPresentation(){
	return this->presentation;
}

void CommandManager::execute(Command* command){
	command->execute();	
	//push stack & clear redo stack
	if(command->isUnexecutable()){			
		this->undoCommandsStack.push(command);
		StackUtil::deleteAllElementsInStack<Command>(this->redoCommandsStack);
	}
	//delete command instance
	else 	
		delete command;
}

void CommandManager::redo(){
	//pop from redo Stack
	Command* command = StackUtil::pop(this->redoCommandsStack,"Cannot redo!");

	if(command == NULL)
		throw Exception("Cannot redo!");

	//push to undo Stack
	this->undoCommandsStack.push(command);

	this->presentation->logMessage("Redo succeed.",true);
	command->execute();
}

void CommandManager::undo(){
	//pop from undo Stack
	Command* command = StackUtil::pop(this->undoCommandsStack,"Cannot undo!");

	if(command == NULL)
		throw Exception("Cannot undo!");
	
	//push to redo Stack
	this->redoCommandsStack.push(command);	

	this->presentation->logMessage("Undo succeed.",true);
	command->unExecute();
}
//pop all command Stack & delete it
void CommandManager::popAllStack(){
	StackUtil::deleteAllElementsInStack<Command>(this->redoCommandsStack);
	StackUtil::deleteAllElementsInStack<Command>(this->undoCommandsStack);
}