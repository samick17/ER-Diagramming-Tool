#pragma once

#include "TextInstruction.h"

class CloseInstruction : public TextInstruction{
public:
    CloseInstruction();
    ~CloseInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};