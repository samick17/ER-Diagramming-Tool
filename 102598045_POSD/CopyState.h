#pragma once

#include "ClipBoardState.h"

class CopyState : public ClipBoardState{
public:
    CopyState(ERModel* erModel);
    ~CopyState();

    bool canPaste();
    void paste();
};