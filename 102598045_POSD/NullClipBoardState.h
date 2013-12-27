#pragma once

#include "ClipBoardState.h"

class NullClipBoardState : public ClipBoardState{
public:
    NullClipBoardState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate);
    ~NullClipBoardState();

    bool canPaste();
    void copy(CommandManager* commandManager,int* newComponentID);
    void paste(CommandManager* commandManager);
};