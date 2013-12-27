#pragma once

#include "ClipBoardState.h"

class NullClipBoardState : public ClipBoardState{
public:
    NullClipBoardState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);
    ~NullClipBoardState();

    bool canPaste();
    void paste(CommandManager* commandManager);
};