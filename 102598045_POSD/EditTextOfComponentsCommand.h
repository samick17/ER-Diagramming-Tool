#pragma once

#include "Command.h"
#include "ERModel.h"
#include "Component.h"
#include <gtest/gtest_prod.h>

class EditTextOfComponentsCommand : public Command{
public:
    EditTextOfComponentsCommand(ERModel* erModel,Component* component,string text);
    ~EditTextOfComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    Component* component;
    string originText;
    string textToSet;
};