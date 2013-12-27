#pragma once

#include "Subject.h"
#include "State.h"

class GraphicalPresentation;
class IObserver;

class StateSubject : public Subject{
    friend class StateSubjectTest;
    FRIEND_TEST(StateSubjectTest,testSwitchState);
    FRIEND_TEST(StateSubjectTest,testDeleteState);
public:
    StateSubject(State* state = NULL);
    ~StateSubject();

    int getStateID();
    void switchState(int stateID,GraphicalPresentation* graphicalPresentation);

    void mousePressEvent(Point position);
    void mouseMoveEvent(Point position);
    void mouseReleaseEvent(Point position);
private:
    void deleteState();
    State* state;
};