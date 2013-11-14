#pragma once

#include "State.h"

class PointerState : public State{
public:
    PointerState(int stateID,GraphicalPresentation* graphicalPresentation);
protected:
   void doMousePressEvent(Point position,Component* component);
   void doMouseMoveEvent(Point position,Component* component);
   void doMouseReleaseEvent(Point position,Component* component);
};