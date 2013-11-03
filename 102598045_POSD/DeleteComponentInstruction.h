#pragma once

#include "TextInstruction.h"

class DeleteComponentInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
};