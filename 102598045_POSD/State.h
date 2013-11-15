#pragma once

#include "GraphicalPresentation.h"

class State{
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);

    int getStateID();

    void mousePressEvent(Point position);
    void mouseMoveEvent(Point position);
    void mouseReleaseEvent(Point position);
protected:
    virtual void doMousePressEvent(Point position) = 0;
    virtual void doMouseMoveEvent(Point position) = 0;
    virtual void doMouseReleaseEvent(Point position) = 0;

    Point getDeltaPosition();

    GraphicalPresentation* graphicalPresentation;
private:
    int stateID;
    Point currentPosition;
    Point deltaPosition;
};