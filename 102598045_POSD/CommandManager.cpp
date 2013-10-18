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

void CommandManager::execute(UnexecutableCommand* command){
	command->execute();		
	this->undoCommandsStack.push(static_cast<UnexecutableCommand*>(command));
	StackUtil::deleteAllElementsInStack<UnexecutableCommand>(this->redoCommandsStack);	
}

void CommandManager::redo(){	
	try{
		//pop from redo Stack	
		UnexecutableCommand* command = StackUtil::pop(this->redoCommandsStack);
		//push to undo Stack
		this->undoCommandsStack.push(command);
		command->execute();
	}
	catch(Exception&){
		throw Exception("Cannot redo!");
	}
}

void CommandManager::undo(){	
	try{
		//pop from undo Stack	
		UnexecutableCommand* command = StackUtil::pop(this->undoCommandsStack);
		//push to redo Stack
		this->redoCommandsStack.push(command);	
		command->unExecute();
	}
	catch(Exception&){
		throw Exception("Cannot undo!");
	}	
}
//pop all command Stack & delete it
void CommandManager::popAllStack(){
	StackUtil::deleteAllElementsInStack<UnexecutableCommand>(this->redoCommandsStack);
	StackUtil::deleteAllElementsInStack<UnexecutableCommand>(this->undoCommandsStack);
}