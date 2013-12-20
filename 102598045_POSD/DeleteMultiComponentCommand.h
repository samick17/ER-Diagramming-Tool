#pragma once

#include <stack>
#include <vector>
#include "Command.h"

class ERModel;
class Component;

using namespace std;

class DeleteMultiComponentCommand : public Command{
public:
    DeleteMultiComponentCommand(ERModel* erModel,vector<string> componentIDVector);
    ~DeleteMultiComponentCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    vector<string> componentIDVector;
    stack<Command*> deleteCommandStack;
};