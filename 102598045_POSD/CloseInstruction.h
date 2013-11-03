#pragma once

#include "TextInstruction.h"

class CloseInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};