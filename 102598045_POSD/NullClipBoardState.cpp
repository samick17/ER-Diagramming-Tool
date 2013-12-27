#include "NullClipBoardState.h"

NullClipBoardState::NullClipBoardState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate) : ClipBoardState(componentMap,clipBoard,componentIDVectorToOperate){
}

NullClipBoardState::~NullClipBoardState(){
}

bool NullClipBoardState::canPaste(){
    return false;
}

void NullClipBoardState::copy(CommandManager* commandManager,int* newComponentID){
}

void NullClipBoardState::paste(CommandManager* commandManager){
    //this is null object, do nothing
}