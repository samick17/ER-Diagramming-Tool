#pragma once

#include "State.h"

class PointerState : public State{
public:
    PointerState(int stateID,GraphicalPresentation* graphicalPresentation);
    ~PointerState();
protected:
   void doMousePressEvent(Point position);
   void doMouseMoveEvent(Point position);
   void doMouseDragEvent(Point position);
   void doMouseReleaseEvent(Point position);
};