#pragma once

#include "Subject.h"
#include "State.h"
#include <set>

class GraphicalPresentation;
class IObserver;

class StateSubject : public Subject{
public:
    StateSubject(State* state = NULL);
    ~StateSubject();

    State* getState() const;
    void switchState(int stateID,GraphicalPresentation* graphicalPresentation);
private:
    State* state;
    void deleteState();
};