#include "ConnectState.h"
#include <iostream>

ConnectState::ConnectState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

ConnectState::~ConnectState(){
}

void ConnectState::onCreate(){
}

void ConnectState::doMousePressEvent(Point position){
	Component* component = this->graphicalPresentation->getLastPressedComponent();
	if(component == NULL)
		cout<<"null component"<<endl;
	else 
		cout<<"press component"<<component->getID()<<endl;
}

void ConnectState::doMouseMoveEvent(Point position){
}

void ConnectState::doMouseReleaseEvent(Point position){
	Component* component = this->graphicalPresentation->getLastReleasedComponent();
	if(component == NULL)
		cout<<"null component"<<endl;
	else 
		cout<<"press component"<<component->getID()<<endl;
}