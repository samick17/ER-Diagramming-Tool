#pragma once

#include "HashMap.h"
#include "Command.h"

class Component;
class ClipBoard;

class PasteComponentsCommand : public Command{
public:
    PasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);
    ~PasteComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    HashMap<string,Component*>& componentMap;
    ClipBoard* clipBoard;
    HashMap<string,Component*> componentMapToCopy;
};