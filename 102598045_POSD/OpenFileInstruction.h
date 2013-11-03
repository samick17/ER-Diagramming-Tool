#pragma once

#include "TextInstruction.h"

class OpenFileInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};