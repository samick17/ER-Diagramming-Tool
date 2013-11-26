#pragma once

#include "Command.h"
#include "Component.h"
#include <gtest/gtest_prod.h>

class EditTextOfComponentsCommand : public Command{
public:
    EditTextOfComponentsCommand(Component* component,string text);
    ~EditTextOfComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    Component* component;
    string originText;
    string textToSet;
};