#include "AddNodeState.h"
#include "StateID.h"

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

void AddNodeState::mousePressEvent(){
}

void AddNodeState::mouseMoveEvent(){
}

void AddNodeState::mouseReleaseEvent(){
    graphicalPresentation->switchState(StateID::PointerState);
}