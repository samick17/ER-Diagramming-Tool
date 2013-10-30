#pragma once

#include "TextInstruction.h"

class DeleteComponentInstruction : public TextInstruction{
public:
    DeleteComponentInstruction();
    ~DeleteComponentInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
};