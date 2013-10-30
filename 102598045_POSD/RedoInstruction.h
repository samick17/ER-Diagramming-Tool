#pragma once

#include "TextInstruction.h"

class RedoInstruction : public TextInstruction{
public:
    RedoInstruction();
    ~RedoInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};