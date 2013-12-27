#pragma once

#include "HashMap.h"
#include <string>

class ERModel;
class Component;
class ClipBoard;
class CommandManager;

using namespace std;

class ClipBoardState{
public:
    ClipBoardState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);
    virtual ~ClipBoardState();

    virtual bool canPaste() = 0;
    virtual void paste(CommandManager* commandManager) = 0;
protected:
    ERModel* erModel;
    HashMap<string,Component*>& componentMap;
    ClipBoard* clipBoard;
};