#pragma once

#include "State.h"
#include "HashMap.h"

class GraphicalPresentation;

typedef State* (*NewStateFunction)(int stateID,GraphicalPresentation* graphicalPresentation);

class StateFactory{
public:
    StateFactory();
    ~StateFactory();

    State* createState(int stateID,GraphicalPresentation* graphicalPresentation);
private:
    HashMap<int,NewStateFunction> newStateMap;
    NewStateFunction findNewStateFunction(int stateID);
    template <typename Type>
    static State* newState(int stateID,GraphicalPresentation* graphicalPresentation);
};

template <typename Type>
State* StateFactory::newState(int stateID,GraphicalPresentation* graphicalPresentation){
    return new Type(stateID,graphicalPresentation);
}