#pragma once

#include "ClipBoardState.h"

class NullClipBoardState : public ClipBoardState{
public:
    NullClipBoardState(ERModel* erModel);
    ~NullClipBoardState();

    bool canPaste();
    void paste();
};