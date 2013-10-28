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
        
    virtual void execute() = 0;
    virtual void unExecute() = 0;
protected:
     bool executionFlag;
};