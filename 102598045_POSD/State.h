#pragma once

#include "GraphicalPresentation.h"

class State{
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);

    int getStateID();

    virtual void mousePressEvent(QPointF position) = 0;
    virtual void mouseMoveEvent(QPointF position) = 0;
    virtual void mouseReleaseEvent(QPointF position) = 0;
protected:
    GraphicalPresentation* graphicalPresentation;
    int stateID;
};