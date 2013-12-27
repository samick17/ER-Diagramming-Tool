#include "DeleteMultiComponentCommand.h"
#include "DeleteComponentCommand.h"
#include "ERModel.h"
#include "Component.h"
#include "StackUtil.h"

DeleteMultiComponentCommand::DeleteMultiComponentCommand(HashMap<string,Component*>& componentMap,HashMap<string,Component*> componentMapToDelete) : componentMap(componentMap),componentMapToDelete(componentMapToDelete){
}

DeleteMultiComponentCommand::~DeleteMultiComponentCommand(){
    StackUtil::deleteAllElementsInStack(this->deleteCommandStack);
}

void DeleteMultiComponentCommand::doExecute(){
    for each(Component* component in this->componentMapToDelete){
        if(!this->componentMap.containsValue(component))
            continue;
        Command* command = new DeleteComponentCommand(this->componentMap,component);
        command->execute();
        this->deleteCommandStack.push(command);
    }
}

void DeleteMultiComponentCommand::doUnExecute(){
    while(!this->deleteCommandStack.empty()){
        Command* command = StackUtil::pop(this->deleteCommandStack);
        command->unExecute();
        delete command;
    }
}