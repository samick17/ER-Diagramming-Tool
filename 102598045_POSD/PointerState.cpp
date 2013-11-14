#include "PointerState.h"
#include <iostream>

PointerState::PointerState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

void PointerState::doMousePressEvent(Point position,Component* component){
	if(component != NULL){
		this->graphicalPresentation->selectWidget(component->getID());
    }
}

void PointerState::doMouseMoveEvent(Point position,Component* component){
	if(component != NULL){
		cout<<"mouse move component"<<endl;
		component->setCenterPosition(position);
	}else{
	    cout<<"mouse move"<<endl;
	}
}

void PointerState::doMouseReleaseEvent(Point position,Component* component){
}