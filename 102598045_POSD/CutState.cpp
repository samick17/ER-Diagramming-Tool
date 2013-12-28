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

void CutState::copy(){
}

void CutState::paste(){
    this->clipBoard->clearData();
}