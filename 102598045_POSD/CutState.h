#pragma once

#include "ClipBoardState.h"

class CutState : public ClipBoardState{
public:
    CutState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate);
    ~CutState();

    void copy();
    void paste();
private:
    HashMap<string,Component*> componentMapToCut;
};