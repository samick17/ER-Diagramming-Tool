#pragma once

#include "Presentation.h"

class TextUI{
public:	
	TextUI(Presentation* presentation);
	~TextUI();
	
	void displayMenu();
	void processCommand();
private:
	Presentation* presentation;
};