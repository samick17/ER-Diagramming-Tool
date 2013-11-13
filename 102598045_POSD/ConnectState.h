#pragma once

#include "State.h"

class ConnectState : public State{
public:
    ConnectState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent(Point position);
   void mouseMoveEvent(Point position);
   void mouseReleaseEvent(Point position);
};