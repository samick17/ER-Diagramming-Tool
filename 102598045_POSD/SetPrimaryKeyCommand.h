#pragma once

#include "Command.h"

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