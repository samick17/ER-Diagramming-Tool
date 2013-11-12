#pragma once

#include "State.h"
#include "HashMap.h"

class AddNodeState : public State{
public:
    AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation);

   void mousePressEvent(QPointF position);
   void mouseMoveEvent(QPointF position);
   void mouseReleaseEvent(QPointF position);

private:
    HashMap<int,string> stateToNodeTypeMap;
};