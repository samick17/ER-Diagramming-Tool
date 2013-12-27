#pragma once

#include "ClipBoardState.h"

class NullClipBoardState : public ClipBoardState{
public:
    NullClipBoardState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate);
    ~NullClipBoardState();

    void copy(CommandManager* commandManager);
    void paste(CommandManager* commandManager);
};