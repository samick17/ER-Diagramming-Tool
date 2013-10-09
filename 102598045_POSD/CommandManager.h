#pragma once

#include "Command.h"
#include "Presentation.h"
#include <stack>

class ERModel;
class TextUI;
class Command;
class Presentation;

typedef pair<string,Command*> CommandPair;

class CommandManager{
public:
	CommandManager(Presentation* presentation);
	~CommandManager();
	
	Presentation* getPresentation();

	void execute(Command* command);
	void redo();
	void undo();

	void popAllStack();
private:
	stack<Command*> redoCommandsStack;
	stack<Command*> undoCommandsStack;
	Presentation* presentation;
};