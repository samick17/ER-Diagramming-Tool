#include "NullClipBoardState.h"

NullClipBoardState::NullClipBoardState(ERModel* erModel) : ClipBoardState(erModel){
}

NullClipBoardState::~NullClipBoardState(){
}

bool NullClipBoardState::canPaste(){
    return false;
}

void NullClipBoardState::paste(){
    //this is null object, do nothing
}