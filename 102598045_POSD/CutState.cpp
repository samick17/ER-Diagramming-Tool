#include "CutState.h"
#include "ERModel.h"
#include "ClipBoardStateID.h"

CutState::CutState(ERModel* erModel) : ClipBoardState(erModel){
}

CutState::~CutState(){
}

bool CutState::canPaste(){
    return true;
}

void CutState::paste(){
    this->erModel->switchClipBoardState(ClipBoardStateID::NullClipBoardState);
}