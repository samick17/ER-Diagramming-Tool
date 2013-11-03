#pragma once

#include "TextInstruction.h"

class RedoInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};