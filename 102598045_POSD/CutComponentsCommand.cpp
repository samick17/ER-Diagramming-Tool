#include "CutComponentsCommand.h"
#include "Component.h"
#include "DeleteMultiComponentCommand.h"

CutComponentsCommand::CutComponentsCommand(HashMap<string,Component*>& componentMap,vector<string> componentIDVector) : componentMap(componentMap),componentIDVector(componentIDVector){
    this->deleteMultiComponentCommand = NULL;
}

CutComponentsCommand::~CutComponentsCommand(){
    if(this->deleteMultiComponentCommand != NULL)
        delete this->deleteMultiComponentCommand;
}

void CutComponentsCommand::doExecute(){
    if(this->deleteMultiComponentCommand == NULL)
        this->deleteMultiComponentCommand = new DeleteMultiComponentCommand(this->componentMap,this->componentIDVector);
    //set clipboard data

    //cut components
    this->deleteMultiComponentCommand->execute();
}

void CutComponentsCommand::doUnExecute(){
    this->deleteMultiComponentCommand->unExecute();
}