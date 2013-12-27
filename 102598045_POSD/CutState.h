#pragma once

#include "ClipBoardState.h"

class CutState : public ClipBoardState{
public:
    CutState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);
    ~CutState();

    bool canPaste();
    void paste(CommandManager* commandManager);
};