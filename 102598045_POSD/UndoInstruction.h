#pragma once

#include "TextInstruction.h"

class UndoInstruction : public TextInstruction{
public:
    UndoInstruction();
    ~UndoInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};