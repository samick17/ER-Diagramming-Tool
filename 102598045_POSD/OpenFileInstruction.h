#pragma once

#include "TextInstruction.h"

class OpenFileInstruction : public TextInstruction{
public:
    OpenFileInstruction();
    ~OpenFileInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};