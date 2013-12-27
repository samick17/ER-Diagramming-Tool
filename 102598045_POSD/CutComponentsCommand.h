#pragma once

#include "Command.h"
#include "HashMap.h"
#include <gtest/gtest_prod.h> 

class Component;
class DeleteMultiComponentCommand;
class ClipBoard;

class CutComponentsCommand : public Command{
public:
    CutComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,HashMap<string,Component*> componentMapToCut);
    ~CutComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ClipBoard* clipBoard;
    DeleteMultiComponentCommand* deleteMultiComponentCommand;
    HashMap<string,Component*>& componentMap;
    HashMap<string,Component*> componentMapToCut;
};