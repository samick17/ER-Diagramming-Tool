#include "PointerState.h"
#include "GraphicalPresentation.h"

PointerState::PointerState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

PointerState::~PointerState(){
}

void PointerState::doMousePressEvent(Point position){
    this->graphicalPresentation->selectWidget();
    this->graphicalPresentation->notify();
}

void PointerState::doMouseMoveEvent(Point position){
}

void PointerState::doMouseDragEvent(Point position){
    this->graphicalPresentation->selectLastPressedWidget();
    this->graphicalPresentation->moveSelectedWidget(this->getDeltaPosition());
}

void PointerState::doMouseReleaseEvent(Point position){
    this->graphicalPresentation->notify();
}