#include "DeleteMultiComponentCommand.h"
#include "DeleteComponentCommand.h"
#include "ERModel.h"
#include "Component.h"
#include "StackUtil.h"

DeleteMultiComponentCommand::DeleteMultiComponentCommand(HashMap<string,Component*>& componentMap,vector<string> componentIDVector) : componentMap(componentMap),componentIDVector(componentIDVector){
}

DeleteMultiComponentCommand::~DeleteMultiComponentCommand(){
    StackUtil::deleteAllElementsInStack(this->deleteCommandStack);
}

void DeleteMultiComponentCommand::doExecute(){
    for each(string componentID in this->componentIDVector){
        try{
            Component* component = this->componentMap.get(componentID);
            Command* command = new DeleteComponentCommand(this->componentMap,component);
            command->execute();
            this->deleteCommandStack.push(command);
        }
        catch(Exception&){
        }
    }
}

void DeleteMultiComponentCommand::doUnExecute(){
    while(!this->deleteCommandStack.empty()){
        Command* command = StackUtil::pop(this->deleteCommandStack);
        command->unExecute();
        delete command;
    }
}