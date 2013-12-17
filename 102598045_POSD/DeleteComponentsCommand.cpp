#include "DeleteComponentsCommand.h"
#include "DeleteComponentCommand.h"
#include "ERModel.h"
#include "Component.h"

DeleteComponentsCommand::DeleteComponentsCommand(ERModel* erModel,vector<string> componentIDVector) : erModel(erModel),componentIDVector(componentIDVector){
}

DeleteComponentsCommand::~DeleteComponentsCommand(){
    for each(Command* command in this->deleteCommandVector){
        delete command;
    }
}

void DeleteComponentsCommand::doExecute(){
    for each(string componentID in this->componentIDVector){
        try{
            Component* component = this->erModel->getComponentByID(componentID);
            Command* command = new DeleteComponentCommand(this->erModel,component);
            command->execute();
            this->deleteCommandVector.push_back(command);
        }
        catch(Exception&){
        }
    }
}

void DeleteComponentsCommand::doUnExecute(){
    for(auto iterator = this->deleteCommandVector.rbegin();iterator != this->deleteCommandVector.rend();iterator++){
        Command* command = *iterator;
        command->unExecute();
        delete command;
    }
    this->deleteCommandVector.clear();
}