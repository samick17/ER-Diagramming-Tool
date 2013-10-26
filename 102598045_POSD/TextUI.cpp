#include "TextUI.h"
#include <iostream>
#include "ApplicationSetting.h"

TextUI::TextUI(Presentation* presentation) : presentation(presentation){
	string title = "Title "+ApplicationSetting::Title;
	system(title.c_str());
}

TextUI::~TextUI(){	
}

void TextUI::displayMenu(){
	this->presentation->displayMenu();
}

void TextUI::processCommand(){	
	string input = this->presentation->getInput();
	this->presentation->processCommand(input);	
}