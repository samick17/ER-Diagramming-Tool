#pragma once

#include "State.h"

class PointerState : public State{
public:
    PointerState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent();
   void mouseMoveEvent();
   void mouseReleaseEvent();
};