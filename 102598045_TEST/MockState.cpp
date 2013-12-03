#include "MockState.h"
#include <stdlib.h>

MockState::MockState() : State(0,NULL){
    this->isDoMousePressEvent = false;
    this->isDoMouseMoveEvent = false;
    this->isDoMouseDragEvent = false;
    this->isDoMouseReleaseEvent = false;
}

void MockState::doMousePressEvent(Point position){
    this->isDoMousePressEvent = true;
}

void MockState::doMouseMoveEvent(Point position){
    this->isDoMouseMoveEvent = true;
}

void MockState::doMouseDragEvent(Point position){
    this->isDoMouseDragEvent = true;
}

void MockState::doMouseReleaseEvent(Point position){
    this->isDoMouseReleaseEvent = true;
}