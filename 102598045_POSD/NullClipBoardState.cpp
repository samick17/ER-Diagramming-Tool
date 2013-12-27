#include "NullClipBoardState.h"

NullClipBoardState::NullClipBoardState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard) : ClipBoardState(erModel,componentMap,clipBoard){
}

NullClipBoardState::~NullClipBoardState(){
}

bool NullClipBoardState::canPaste(){
    return false;
}

void NullClipBoardState::paste(CommandManager* commandManager){
    //this is null object, do nothing
}