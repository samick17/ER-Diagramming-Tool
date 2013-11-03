#pragma once

#include "TextInstruction.h"

class SaveFileInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};