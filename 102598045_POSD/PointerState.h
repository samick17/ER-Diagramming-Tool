#pragma once

#include "State.h"

class PointerState : public State{
public:
    PointerState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent(Point position);
   void mouseMoveEvent(Point position);
   void mouseReleaseEvent(Point position);
};