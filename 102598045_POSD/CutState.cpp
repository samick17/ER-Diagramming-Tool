#include "CutState.h"
#include "ERModel.h"
#include "ClipBoardStateID.h"
#include "CommandFactory.h"

CutState::CutState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate) : ClipBoardState(componentMap,clipBoard,componentIDVectorToOperate){
    for each(string componentID in componentIDVectorToOperate){
        if(componentMap.containsKey(componentID))
            this->componentMapToCut.put(componentID,componentMap.get(componentID));
    }
}

CutState::~CutState(){
}

bool CutState::canPaste(){
    return true;
}

void CutState::copy(CommandManager* commandManager,int* newComponentID){
    if(componentMapToCut.empty())
        return;
    clipBoard->setData(this->componentMapToCut);
    CommandFactory commandFactory;
    Command* command = commandFactory.createCutComponentsCommand(this->componentMap,this->clipBoard,this->componentMapToCut);
    commandManager->execute(command);
}

void CutState::paste(CommandManager* commandManager){
    HashMap<string,Component*> componentMapToCopy = clipBoard->getData();
    CommandFactory commandFactory;
    Command* command = commandFactory.createPasteComponentsCommand(this->componentMap,this->clipBoard);
    commandManager->execute(command);
    this->clipBoard->clearData();
}