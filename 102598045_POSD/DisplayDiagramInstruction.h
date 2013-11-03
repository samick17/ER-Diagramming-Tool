#pragma once

#include "TextInstruction.h"

class DisplayDiagramInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};