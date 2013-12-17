#pragma once

#include <vector>
#include "Command.h"

class ERModel;
class Component;

using namespace std;

class DeleteComponentsCommand : public Command{
public:
    DeleteComponentsCommand(ERModel* erModel,vector<string> componentIDVector);
    ~DeleteComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    vector<string> componentIDVector;
    vector<Command*> deleteCommandVector;
};