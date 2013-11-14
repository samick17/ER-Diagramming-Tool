#pragma once

#include "GraphicalPresentation.h"

class State{
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);

    int getStateID();

    void mousePressEvent(Point position,Component* component);
    void mouseMoveEvent(Point position,Component* component);
    void mouseReleaseEvent(Point position,Component* component);
protected:
    virtual void doMousePressEvent(Point position,Component* component) = 0;
    virtual void doMouseMoveEvent(Point position,Component* component) = 0;
    virtual void doMouseReleaseEvent(Point position,Component* component) = 0;

    Point getDeltaPosition();

    GraphicalPresentation* graphicalPresentation;
private:
    int stateID;
    Point currentPosition;
    Point deltaPosition;
};