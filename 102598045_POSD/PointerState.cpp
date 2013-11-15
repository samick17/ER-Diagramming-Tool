#include "PointerState.h"
#include <iostream>

PointerState::PointerState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

void PointerState::doMousePressEvent(Point position){
	this->graphicalPresentation->selectWidget();
}

void PointerState::doMouseMoveEvent(Point position){
	this->graphicalPresentation->moveSelectedWidget(this->getDeltaPosition());
}

void PointerState::doMouseReleaseEvent(Point position){
}