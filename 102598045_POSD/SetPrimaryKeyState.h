#pragma once

#include "State.h"

class SetPrimaryKeyState : public State{
public:
    SetPrimaryKeyState(int stateID,GraphicalPresentation* graphicalPresentation);
    ~SetPrimaryKeyState();
protected:
   void doMousePressEvent(Point position);
   void doMouseMoveEvent(Point position);
   void doMouseDragEvent(Point position);
   void doMouseReleaseEvent(Point position);
};