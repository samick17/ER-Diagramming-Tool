#pragma once

#include "TextPresentation.h"
#include "TextUIPresenter.h"
#include <iostream>

class TextInstruction{
public:
    TextInstruction();
    ~TextInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter) = 0;
private:
};