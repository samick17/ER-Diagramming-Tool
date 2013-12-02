#include "StateSubject.h"
#include "StateFactory.h"

StateSubject::StateSubject(State* state) : state(state){
}

StateSubject::~StateSubject(){
    this->deleteState();
}

State* StateSubject::getState() const{
    return this->state;
}

void StateSubject::switchState(int stateID,GraphicalPresentation* graphicalPresentation){
    this->deleteState();
    StateFactory stateFactory;
    this->state = stateFactory.createState(stateID,graphicalPresentation);
    this->notify();
    this->state->onCreate();
}

void StateSubject::deleteState(){
    if(this->state){
        delete this->state;
        this->state = NULL;
    }
}