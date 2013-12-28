#include "CopyState.h"
#include "ClipBoard.h"
#include "CommandFactory.h"
#include "CommandManager.h"
#include "HashMapUtil.h"
#include "Node.h"
#include "StringUtil.h"

CopyState::CopyState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate) : ClipBoardState(clipBoard,componentMap,componentIDVectorToOperate){
    for each(string componentID in componentIDVectorToOperate){
        if(componentMap.containsKey(componentID))
            this->componentMapToCopy.put(componentID,componentMap.get(componentID));
    }
    this->flag = false;
    this->executeCount = 0;
}

CopyState::~CopyState(){
}

void CopyState::copy(){
}

void CopyState::paste(){
}