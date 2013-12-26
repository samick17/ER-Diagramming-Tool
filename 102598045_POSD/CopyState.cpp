#include "CopyState.h"

CopyState::CopyState(ERModel* erModel) : ClipBoardState(erModel){
}

CopyState::~CopyState(){
}

bool CopyState::canPaste(){
    return true;
}

void CopyState::paste(){
}