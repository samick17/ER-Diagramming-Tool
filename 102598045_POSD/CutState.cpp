#include "CutState.h"
#include "ERModel.h"
#include "ClipBoardStateID.h"
#include "CommandFactory.h"

CutState::CutState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate) : ClipBoardState(clipBoard,componentMap,componentIDVectorToOperate){
    for each(string componentID in componentIDVectorToOperate){
        if(componentMap.containsKey(componentID))
            this->componentMapToCut.put(componentID,componentMap.get(componentID));
    }
}

CutState::~CutState(){
}

void CutState::copy(CommandManager* commandManager){
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