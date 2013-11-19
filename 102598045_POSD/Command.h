#pragma once

#include <string>
#include "Component.h"
#include "TextPresentation.h"

using namespace std;

class Presentation;
class TextUI;
class ERModel;

class Command{
public:
    Command();
    virtual ~Command();
    void execute();
    void unExecute();
protected:
    virtual void doExecute() = 0;
    virtual void doUnExecute() = 0;
    bool getExecutionFalg();
private:
    bool executionFlag;
};