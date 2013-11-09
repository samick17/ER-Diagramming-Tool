#include "AddNodeState.h"
#include "StateID.h"

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

void AddNodeState::mousePressEvent(QPointF position){
}

void AddNodeState::mouseMoveEvent(QPointF position){
}

void AddNodeState::mouseReleaseEvent(QPointF position){
    graphicalPresentation->switchState(StateID::PointerState);
}