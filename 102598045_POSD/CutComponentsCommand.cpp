#include "CutComponentsCommand.h"
#include "Component.h"
#include "DeleteMultiComponentCommand.h"
#include "ClipBoard.h"

CutComponentsCommand::CutComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,HashMap<string,Component*> componentMapToCut) : componentMap(componentMap),clipBoard(clipBoard),componentMapToCut(componentMapToCut){
    this->deleteMultiComponentCommand = NULL;
}

CutComponentsCommand::~CutComponentsCommand(){
    if(this->deleteMultiComponentCommand != NULL)
        delete this->deleteMultiComponentCommand;
}

void CutComponentsCommand::doExecute(){
    if(this->deleteMultiComponentCommand == NULL)
        this->deleteMultiComponentCommand = new DeleteMultiComponentCommand(this->componentMap,this->componentMapToCut);
    //set clipboard data
    this->clipBoard->setData(componentMapToCut);
    //cut components
    this->deleteMultiComponentCommand->execute();
}

void CutComponentsCommand::doUnExecute(){
    this->deleteMultiComponentCommand->unExecute();
    this->clipBoard->clearData();
}