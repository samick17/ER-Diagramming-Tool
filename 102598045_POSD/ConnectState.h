#pragma once

#include "State.h"

class ConnectState : public State{
public:
    ConnectState(int stateID,GraphicalPresentation* graphicalPresentation);
protected:
   void doMousePressEvent(Point position);
   void doMouseMoveEvent(Point position);
   void doMouseReleaseEvent(Point position);
};