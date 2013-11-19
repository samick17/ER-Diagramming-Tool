#pragma once

#include "State.h"

class ConnectState : public State{
public:
    ConnectState(int stateID,GraphicalPresentation* graphicalPresentation);
    ~ConnectState();
    void onCreate();
protected:
   void doMousePressEvent(Point position);
   void doMouseMoveEvent(Point position);
   void doMouseDragEvent(Point position);
   void doMouseReleaseEvent(Point position);
};