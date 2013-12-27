#pragma once

#include "HashMap.h"
#include <string>

class Component;
class ClipBoard;
class CommandManager;

using namespace std;

class ClipBoardState{
public:
    ClipBoardState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate);
    virtual ~ClipBoardState();

    virtual bool canPaste() = 0;
    virtual void copy(CommandManager* commandManager,int* newComponentID) = 0;
    virtual void paste(CommandManager* commandManager) = 0;
protected:
    HashMap<string,Component*>& componentMap;
    ClipBoard* clipBoard;
    vector<string> componentIDVectorToOperate;
};