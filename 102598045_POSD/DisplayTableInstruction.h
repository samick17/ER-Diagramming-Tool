#pragma once

#include "TextInstruction.h"

class DisplayTableInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};