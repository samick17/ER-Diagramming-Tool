#pragma once

#include "Command.h"

class PasteComponentsCommand : public Command{
public:
    PasteComponentsCommand();
    ~PasteComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
};