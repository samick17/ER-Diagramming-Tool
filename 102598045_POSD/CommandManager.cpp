#include "CommandManager.h"
#include "StackUtil.h"
#include "Exception.h"

using namespace std;

CommandManager::CommandManager(){
}

CommandManager::~CommandManager(){
    this->popAllStack();
}

void CommandManager::execute(Command* command){
    command->execute();
    this->undoCommandsStack.push(command);
    StackUtil::deleteAllElementsInStack<Command>(this->redoCommandsStack);
}

void CommandManager::redo(){
    try{
        //pop from redo Stack
        Command* command = StackUtil::pop(this->redoCommandsStack);
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
        Command* command = StackUtil::pop(this->undoCommandsStack);
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
    StackUtil::deleteAllElementsInStack<Command>(this->redoCommandsStack);
    StackUtil::deleteAllElementsInStack<Command>(this->undoCommandsStack);
}