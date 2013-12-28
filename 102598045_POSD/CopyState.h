#pragma once

#include "ClipBoardState.h"

using namespace std;

class CopyState : public ClipBoardState{
public:
    CopyState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate);
    ~CopyState();

    void copy();
    void paste();
private:
    HashMap<string,Component*> componentMapToCopy;
    HashMap<string,Component*> clonedComponentMap;
    int* newComponentID;
    int executeCount;
    bool flag;
};