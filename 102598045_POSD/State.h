#pragma once

#include "GraphicalPresentation.h"

class State{
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);

    int getStateID();

    virtual void mousePressEvent(Point position) = 0;
    virtual void mouseMoveEvent(Point position) = 0;
    virtual void mouseReleaseEvent(Point position) = 0;
protected:
    GraphicalPresentation* graphicalPresentation;
    int stateID;
    Point currentPosition;
};