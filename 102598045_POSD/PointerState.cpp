#include "PointerState.h"
#include "GraphicalPresentation.h"

PointerState::PointerState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

PointerState::~PointerState(){
}

void PointerState::doMousePressEvent(Point position){
    this->graphicalPresentation->selectWidget();
    this->mousePressPosition = position;
    this->graphicalPresentation->notifyModel();
}

void PointerState::doMouseMoveEvent(Point position){
}

void PointerState::doMouseDragEvent(Point position){
    this->graphicalPresentation->selectLastPressedWidget();
    this->graphicalPresentation->previewMoveSelectedWidget(this->getDeltaPosition());
    this->graphicalPresentation->notifyModel();
}

void PointerState::doMouseReleaseEvent(Point position){
    this->mouseReleasePosition = position;
    Point deltaPosition = this->mousePressPosition - this->mouseReleasePosition;
    this->graphicalPresentation->previewMoveSelectedWidget(deltaPosition);
    this->graphicalPresentation->moveSelectedWidget(this->mousePressPosition,this->mouseReleasePosition);
    this->graphicalPresentation->notifyModel();
}