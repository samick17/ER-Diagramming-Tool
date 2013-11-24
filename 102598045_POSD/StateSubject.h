#pragma once

#include "Subject.h"
#include "State.h"
#include <set>

class GraphicalPresentation;
class IObserver;

class StateSubject : public Subject{
    friend class StateSubjectTest;
    FRIEND_TEST(StateSubjectTest,testSwitchState);
    FRIEND_TEST(StateSubjectTest,testDeleteState);
public:
    StateSubject(State* state = NULL);
    ~StateSubject();

    State* getState() const;
    void switchState(int stateID,GraphicalPresentation* graphicalPresentation);
private:
    void deleteState();
    State* state;
};