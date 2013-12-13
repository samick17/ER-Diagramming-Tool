#include "PointerState.h"
#include "GraphicalPresentation.h"

PointerState::PointerState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

PointerState::~PointerState(){
}

void PointerState::doMousePressEvent(Point position){
    this->graphicalPresentation->selectWidget();
    this->mousePressPosition = position;
    this->graphicalPresentation->notify();
}

void PointerState::doMouseMoveEvent(Point position){
}

void PointerState::doMouseDragEvent(Point position){
    this->graphicalPresentation->selectLastPressedWidget();
    this->graphicalPresentation->previewMoveSelectedWidget(this->getDeltaPosition());
    this->graphicalPresentation->notify();
}

void PointerState::doMouseReleaseEvent(Point position){
    this->mouseReleasePosition = position;
    this->graphicalPresentation->moveSelectedWidget(this->mousePressPosition,this->mouseReleasePosition);
    this->graphicalPresentation->notify();
}