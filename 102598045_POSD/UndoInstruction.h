#pragma once

#include "TextInstruction.h"

class UndoInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};