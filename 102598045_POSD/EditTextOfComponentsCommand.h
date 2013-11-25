#pragma once

#include "Command.h"

class EditTextOfComponentsCommand : public Command{
public:
    EditTextOfComponentsCommand(ERModel* erModel,Component* component,string name);
    ~EditTextOfComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    Component* component;
};