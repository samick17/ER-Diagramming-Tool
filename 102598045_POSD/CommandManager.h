#pragma once

#include "UnexecutableCommand.h"
#include "Presentation.h"
#include <stack>

class ERModel;
class TextUI;
class Command;
class Presentation;

class CommandManager{
public:
	CommandManager(Presentation* presentation);
	~CommandManager();
	
	Presentation* getPresentation();

	void execute(UnexecutableCommand* command);
	void redo();
	void undo();

	void popAllStack();
private:
	stack<UnexecutableCommand*> redoCommandsStack;
	stack<UnexecutableCommand*> undoCommandsStack;
	Presentation* presentation;
};