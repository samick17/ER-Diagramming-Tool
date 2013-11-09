#include "State.h"

State::State(int stateID,GraphicalPresentation* graphicalPresentation) : stateID(stateID),graphicalPresentation(graphicalPresentation){
}

int State::getStateID(){
    return this->stateID;
}