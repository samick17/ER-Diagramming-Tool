#pragma once

#include "State.h"
#include "HashMap.h"

class AddNodeState : public State{
public:
    AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation);
    ~AddNodeState();
    void onCreate();
protected:
   void doMousePressEvent(Point position);
   void doMouseMoveEvent(Point position);
   void doMouseDragEvent(Point position);
   void doMouseReleaseEvent(Point position);
private:
    inline void previewAddedNode(Point position);
    HashMap<int,string> stateToNodeTypeMap;
};