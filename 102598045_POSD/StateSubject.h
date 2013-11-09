#pragma once

#include "ISubject.h"
#include "State.h"
#include <set>

class GraphicalPresentation;
class IObserver;

class StateSubject : public ISubject{
public:
    StateSubject(State* state = NULL);
    ~StateSubject();

    State* getState() const;

    void switchState(int stateID,GraphicalPresentation* graphicalPresentation);
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);
private:
    State* state;
    set<IObserver*> observerSet;
    void deleteState();
};