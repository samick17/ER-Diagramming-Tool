#pragma once

#include "HashMap.h"
#include "Command.h"

class Component;
class ClipBoard;
class ClipBoardState;

class PasteComponentsCommand : public Command{
public:
    PasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,ClipBoardState* clipBoardState,int* newComponentID);
    ~PasteComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    HashMap<string,Component*>& componentMap;
    ClipBoard* clipBoard;
    ClipBoardState* clipBoardState;
    HashMap<string,Component*> componentMapToCopy;
    int* newComponentID;
};