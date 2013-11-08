#include "AddNodeState.h"
#include "StateID.h"
#include <iostream>

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

void AddNodeState::mousePressEvent(){
	cout<<"press"<<endl;
}

void AddNodeState::mouseMoveEvent(){
	cout<<"move"<<endl;
}

void AddNodeState::mouseReleaseEvent(){
	cout<<"release"<<endl;
    graphicalPresentation->switchState(StateID::PointerState);
}