#pragma once

#include "ClipBoardState.h"

class CopyState : public ClipBoardState{
public:
    CopyState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);
    ~CopyState();

    bool canPaste();
    void paste(CommandManager* commandManager);
};