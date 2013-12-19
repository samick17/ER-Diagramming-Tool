#include "DeleteComponentsCommand.h"
#include "DeleteComponentCommand.h"
#include "ERModel.h"
#include "Component.h"
#include "StackUtil.h"

DeleteComponentsCommand::DeleteComponentsCommand(ERModel* erModel,vector<string> componentIDVector) : erModel(erModel),componentIDVector(componentIDVector){
}

DeleteComponentsCommand::~DeleteComponentsCommand(){
    StackUtil::deleteAllElementsInStack(this->deleteCommandStack);
}

void DeleteComponentsCommand::doExecute(){
    for each(string componentID in this->componentIDVector){
        try{
            Component* component = this->erModel->getComponentByID(componentID);
            Command* command = new DeleteComponentCommand(this->erModel,component);
            command->execute();
            this->deleteCommandStack.push(command);
        }
        catch(Exception&){
        }
    }
}

void DeleteComponentsCommand::doUnExecute(){
    while(!this->deleteCommandStack.empty()){
        Command* command = StackUtil::pop(this->deleteCommandStack);
        command->unExecute();
        delete command;
    }
}