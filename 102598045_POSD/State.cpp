#include "State.h"

State::State(int stateID,GraphicalPresentation* graphicalPresentation) : stateID(stateID),graphicalPresentation(graphicalPresentation){
    this->isMousePressed = false;
}

State::~State(){
}

int State::getStateID(){
    return this->stateID;
}

void State::mousePressEvent(Point position){
    this->isMousePressed = true;
    this->currentPosition = position;
    this->deltaPosition = Point();
    this->doMousePressEvent(position);
}

void State::mouseMoveEvent(Point position){
    this->deltaPosition = position-this->currentPosition;
    if(this->isMousePressed)
        this->doMouseDragEvent(position);
    else
        this->doMouseMoveEvent(position);
    this->currentPosition = position;
}

void State::mouseReleaseEvent(Point position){
    this->isMousePressed = false;
    this->doMouseReleaseEvent(position);
}

Point State::getDeltaPosition(){
    return this->deltaPosition;
}