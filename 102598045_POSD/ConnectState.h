#pragma once

#include "State.h"

class ConnectState : public State{
public:
    ConnectState(int stateID,GraphicalPresentation* graphicalPresentation);
protected:
   void doMousePressEvent(Point position,Component* component);
   void doMouseMoveEvent(Point position,Component* component);
   void doMouseReleaseEvent(Point position,Component* component);
};