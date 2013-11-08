#pragma once

#include "State.h"

class ConnectState : public State{
public:
    ConnectState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent();
   void mouseMoveEvent();
   void mouseReleaseEvent();
};