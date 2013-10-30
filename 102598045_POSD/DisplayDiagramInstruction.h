#pragma once

#include "TextInstruction.h"

class DisplayDiagramInstruction : public TextInstruction{
public:
    DisplayDiagramInstruction();
    ~DisplayDiagramInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};