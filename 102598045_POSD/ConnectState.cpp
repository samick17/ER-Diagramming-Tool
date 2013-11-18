#include "ConnectState.h"

ConnectState::ConnectState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

ConnectState::~ConnectState(){
}

void ConnectState::onCreate(){
}

void ConnectState::doMousePressEvent(Point position){
}

void ConnectState::doMouseMoveEvent(Point position){
}

void ConnectState::doMouseReleaseEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastReleasedComponent();
    if(sourceComponent && targetComponent)
        this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
}