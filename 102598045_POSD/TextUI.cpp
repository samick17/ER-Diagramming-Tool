#include "TextUI.h"
#include "TextUIPresenter.h"
#include <iostream>

TextUI::TextUI(TextPresentation* textPresentation) : textPresentation(textPresentation){
    this->textPresentation->registerObserver(this);
}

TextUI::~TextUI(){
    this->textPresentation->unregisterObserver(this);
}

void TextUI::displayMenu(){
    this->textPresentation->displayMenu();
}

void TextUI::processCommand(){
    this->textPresentation->processCommand();
}

void TextUI::notify(int notifiedEventType){
    this->textPresentation->executeNotify(notifiedEventType);
}