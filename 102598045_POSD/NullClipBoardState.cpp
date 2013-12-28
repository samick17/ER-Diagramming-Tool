#include "NullClipBoardState.h"

NullClipBoardState::NullClipBoardState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate) : ClipBoardState(clipBoard,componentMap,componentIDVectorToOperate){
}

NullClipBoardState::~NullClipBoardState(){
}

void NullClipBoardState::copy(){
}

void NullClipBoardState::paste(){
    //this is null object, do nothing
}