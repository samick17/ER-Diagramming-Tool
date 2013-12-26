#pragma once

#include "Command.h"
#include "HashMap.h"
#include <gtest/gtest_prod.h> 

class Component;
class DeleteMultiComponentCommand;

class CutComponentsCommand : public Command{
public:
    CutComponentsCommand(HashMap<string,Component*>& componentMap,vector<string> componentIDVector);
    ~CutComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    DeleteMultiComponentCommand* deleteMultiComponentCommand;
    HashMap<string,Component*>& componentMap;
    vector<string> componentIDVector;
};