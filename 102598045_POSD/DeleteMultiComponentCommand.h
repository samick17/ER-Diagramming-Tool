#pragma once

#include <stack>
#include "HashMap.h"
#include "Command.h"

class Component;

using namespace std;

class DeleteMultiComponentCommand : public Command{
public:
    DeleteMultiComponentCommand(HashMap<string,Component*>& componentMap,HashMap<string,Component*> componentMapToDelete);
    ~DeleteMultiComponentCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    HashMap<string,Component*>& componentMap;
    HashMap<string,Component*> componentMapToDelete;
    stack<Command*> deleteCommandStack;
};