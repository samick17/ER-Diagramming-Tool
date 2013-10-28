#pragma once

#include <string>
#include "TextPresentation.h"
#include "Command.h"

using namespace std;

typedef void (TextPresentation::*CommandInstruction)();

struct CommandData{
public:
    CommandData(string key,string info,CommandInstruction commandInstruction);
    ~CommandData();

    string getKey();
    string getInfo();
    CommandInstruction getCommandInstruction();
private:
    string key;
    string info;
    CommandInstruction commandInstruction;
};