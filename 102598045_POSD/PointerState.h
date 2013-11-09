#pragma once

#include "State.h"

class PointerState : public State{
public:
    PointerState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent(QPointF position);
   void mouseMoveEvent(QPointF position);
   void mouseReleaseEvent(QPointF position);
};