#pragma once

#include "ClipBoardState.h"

class CutState : public ClipBoardState{
public:
    CutState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate);
    ~CutState();

    bool canPaste();
    void copy(CommandManager* commandManager,int* newComponentID);
    void paste(CommandManager* commandManager);
private:
    HashMap<string,Component*> componentMapToCut;
};