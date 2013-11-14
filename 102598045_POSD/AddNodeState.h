#pragma once

#include "State.h"
#include "HashMap.h"

class AddNodeState : public State{
public:
    AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation);
protected:
   void doMousePressEvent(Point position,Component* component);
   void doMouseMoveEvent(Point position,Component* component);
   void doMouseReleaseEvent(Point position,Component* component);
private:
    HashMap<int,string> stateToNodeTypeMap;
};