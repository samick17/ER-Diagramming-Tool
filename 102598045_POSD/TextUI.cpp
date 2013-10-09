#include "TextUI.h"
#include <iostream>

TextUI::TextUI(Presentation* presentation) : presentation(presentation){
}

TextUI::~TextUI(){	
}

bool TextUI::isAlive(){
	return this->presentation->isAlive();
}

void TextUI::displayMenu(){
	this->presentation->displayMenu();
}

void TextUI::processCommand(){	
	string input = this->presentation->getInput();
	this->presentation->processCommand(input);	
}