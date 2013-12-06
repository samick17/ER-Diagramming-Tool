#pragma once

#include "Command.h"

class MockCommand : public Command{
public:
    MockCommand();
    ~MockCommand();

    void doExecute();
    void doUnExecute();
    int getExecutionValue();
private:
    int executionValue;
};