#include "SetPrimaryKeyState.h"
#include "GraphicalPresentation.h"

SetPrimaryKeyState::SetPrimaryKeyState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

SetPrimaryKeyState::~SetPrimaryKeyState(){
}

void SetPrimaryKeyState::doMousePressEvent(Point position){
    Component* component = this->graphicalPresentation->getLastPressedComponent();
    if(!component)
        return;
    this->graphicalPresentation->setPrimaryKey(component->getID());
}

void SetPrimaryKeyState::doMouseMoveEvent(Point position){
}

void SetPrimaryKeyState::doMouseDragEvent(Point position){
}

void SetPrimaryKeyState::doMouseReleaseEvent(Point position){
}