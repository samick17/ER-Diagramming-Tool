#include "State.h"

State::State(int stateID,GraphicalPresentation* graphicalPresentation) : stateID(stateID),graphicalPresentation(graphicalPresentation){
}

int State::getStateID(){
    return this->stateID;
}

void State::mousePressEvent(Point position,Component* component){
	this->currentPosition = position;
	this->deltaPosition = Point::DefaultPoint();
	this->doMousePressEvent(position,component);
}

void State::mouseMoveEvent(Point position,Component* component){
    this->deltaPosition = position-this->currentPosition;
    this->doMouseMoveEvent(position,component);
    this->currentPosition = position;
}

void State::mouseReleaseEvent(Point position,Component* component){
    this->doMouseReleaseEvent(position,component);
}

Point State::getDeltaPosition(){
    return this->deltaPosition;
}