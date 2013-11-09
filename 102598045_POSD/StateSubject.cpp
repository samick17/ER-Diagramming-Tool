#include "StateSubject.h"
#include "StateFactory.h"
#include "IObserver.h"

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
    notify();
}

void StateSubject::registerObserver(IObserver* observer){
    this->observerSet.insert(observer);
}

void StateSubject::unregisterObserver(IObserver* observer){
    this->observerSet.erase(observer);
}

void StateSubject::notify(){
    for each(IObserver* observer in this->observerSet)
       observer->notify(this);
}

void StateSubject::notify(IObserver* observer){
    observer->notify(this);
}

void StateSubject::deleteState(){
    if(this->state != NULL)
        delete this->state;
}