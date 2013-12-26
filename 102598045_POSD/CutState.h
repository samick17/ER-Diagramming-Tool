#pragma once

#include "ClipBoardState.h"

class CutState : public ClipBoardState{
public:
    CutState(ERModel* erModel);
    ~CutState();

    bool canPaste();
    void paste();
};