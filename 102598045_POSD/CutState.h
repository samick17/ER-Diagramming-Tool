#pragma once

#include "ClipBoardState.h"

class CutState : public ClipBoardState{
public:
    CutState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate);
    ~CutState();

    void copy(CommandManager* commandManager);
    void paste(CommandManager* commandManager);
private:
    HashMap<string,Component*> componentMapToCut;
};