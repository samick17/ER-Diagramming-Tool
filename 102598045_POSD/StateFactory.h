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
    template <typename Type>
    static State* newState(int stateID,GraphicalPresentation* graphicalPresentation);

    NewStateFunction findNewStateFunction(int stateID);
    HashMap<int,NewStateFunction> newStateMap;
};

template <typename Type>
State* StateFactory::newState(int stateID,GraphicalPresentation* graphicalPresentation){
    return new Type(stateID,graphicalPresentation);
}