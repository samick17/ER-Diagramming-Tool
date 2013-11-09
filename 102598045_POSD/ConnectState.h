#pragma once

#include "State.h"

class ConnectState : public State{
public:
    ConnectState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent(QPointF position);
   void mouseMoveEvent(QPointF position);
   void mouseReleaseEvent(QPointF position);
};