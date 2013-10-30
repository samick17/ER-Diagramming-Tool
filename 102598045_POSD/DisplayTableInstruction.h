#pragma once

#include "TextInstruction.h"

class DisplayTableInstruction : public TextInstruction{
public:
    DisplayTableInstruction();
    ~DisplayTableInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};