#pragma once

#include "State.h"

class AddNodeState : public State{
public:
    AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent();
   void mouseMoveEvent();
   void mouseReleaseEvent();
};