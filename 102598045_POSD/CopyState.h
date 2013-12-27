#pragma once

#include "ClipBoardState.h"
#include <stack>

using namespace std;

class CopyState : public ClipBoardState{
public:
    CopyState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate);
    ~CopyState();

    bool canPaste();
    void copy(CommandManager* commandManager,int* newComponentID);
    void paste(CommandManager* commandManager);
private:
    HashMap<string,Component*> componentMapToCopy;
    HashMap<string,Component*> clonedComponentMap;
    stack<CopyState> copyStateStack;
    int* newComponentID;
    bool flag;
};