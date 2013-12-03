#pragma once
#include "State.h"

class MockState : public State{
public:
    MockState();
    bool isDoMousePressEvent,isDoMouseMoveEvent,isDoMouseDragEvent,isDoMouseReleaseEvent;
protected:
    void doMousePressEvent(Point position);
    void doMouseMoveEvent(Point position);
    void doMouseDragEvent(Point position);
    void doMouseReleaseEvent(Point position);
};