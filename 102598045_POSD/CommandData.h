#pragma once

#include <string>
#include "Presentation.h"
#include "Command.h"

using namespace std;

class Presentation;

typedef Command* (*NewCommandFunction)(Presentation*);

struct CommandData{
public:
	CommandData(string key,string info,NewCommandFunction newCommandFunc);
	~CommandData();

	string getKey();
	string getInfo();
	NewCommandFunction getNewCommandFunction();
private:
	string key;
	string info;
	NewCommandFunction newCommandFunction;
};