#pragma once

#include "State.h"
#include "HashMap.h"

class AddNodeState : public State{
public:
    AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent(Point position);
   void mouseMoveEvent(Point position);
   void mouseReleaseEvent(Point position);
private:
    HashMap<int,string> stateToNodeTypeMap;
};