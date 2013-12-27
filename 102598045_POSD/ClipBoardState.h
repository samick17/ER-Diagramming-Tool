#pragma once

#include "HashMap.h"
#include <string>

class Component;
class ClipBoard;
class CommandManager;

using namespace std;

class ClipBoardState{
public:
    ClipBoardState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate);
    virtual ~ClipBoardState();

    virtual void copy(CommandManager* commandManager) = 0;
    virtual void paste(CommandManager* commandManager) = 0;
protected:
    ClipBoard* clipBoard;
    HashMap<string,Component*>& componentMap;
    vector<string> componentIDVectorToOperate;
};