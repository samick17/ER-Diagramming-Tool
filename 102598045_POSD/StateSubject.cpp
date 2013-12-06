#include "StateSubject.h"
#include "StateFactory.h"

StateSubject::StateSubject(State* state) : state(state){
}

StateSubject::~StateSubject(){
    this->deleteState();
}

int StateSubject::getStateID(){
    return this->state->getStateID();
}

void StateSubject::switchState(int stateID,GraphicalPresentation* graphicalPresentation){
    this->deleteState();
    StateFactory stateFactory;
    this->state = stateFactory.createState(stateID,graphicalPresentation);
    this->notify();
    this->state->onCreate();
}

void StateSubject::mousePressEvent(Point position){
    this->state->mousePressEvent(position);
}

void StateSubject::mouseMoveEvent(Point position){
    this->state->mouseMoveEvent(position);
}

void StateSubject::mouseReleaseEvent(Point position){
    this->state->mouseReleaseEvent(position);
}

void StateSubject::deleteState(){
    if(this->state){
        delete this->state;
        this->state = NULL;
    }
}