#include "PointerState.h"
#include <iostream>

PointerState::PointerState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

void PointerState::mousePressEvent(Point position){
	cout<<"press scene"<<endl;
}

void PointerState::mouseMoveEvent(Point position){
}

void PointerState::mouseReleaseEvent(Point position){
}