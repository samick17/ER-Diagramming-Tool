#pragma once

#include "Command.h"
#include <gtest/gtest_prod.h>

class Attribute;

class SetPrimaryKeyCommand : public Command{
public:
    SetPrimaryKeyCommand(Attribute* attribute);
    ~SetPrimaryKeyCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    Attribute* attribute;
    bool isPrimaryKey;
};