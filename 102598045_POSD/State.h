#pragma once

#include "GraphicalPresentation.h"

class State{
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);

    virtual void mousePressEvent() = 0;
    virtual void mouseMoveEvent() = 0;
    virtual void mouseReleaseEvent() = 0;
protected:
    GraphicalPresentation* graphicalPresentation;
};