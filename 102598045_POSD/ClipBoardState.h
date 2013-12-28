#pragma once

#include "HashMap.h"
#include <string>

class Component;
class ClipBoard;

using namespace std;

class ClipBoardState{
public:
    ClipBoardState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate);
    virtual ~ClipBoardState();

    virtual void copy() = 0;
    virtual void paste() = 0;
protected:
    ClipBoard* clipBoard;
    HashMap<string,Component*>& componentMap;
    vector<string> componentIDVectorToOperate;
};