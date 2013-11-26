#pragma once

#include "Command.h"
#include <gtest/gtest_prod.h>

class ERModel;
class Attribute;

class SetPrimaryKeyCommand : public Command{
public:
    SetPrimaryKeyCommand(ERModel* erModel,Attribute* attribute);
    ~SetPrimaryKeyCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    Attribute* attribute;
    bool isPrimaryKey;
};