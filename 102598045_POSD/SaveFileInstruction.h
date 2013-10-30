#pragma once

#include "TextInstruction.h"

class SaveFileInstruction : public TextInstruction{
public:
    SaveFileInstruction();
    ~SaveFileInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};