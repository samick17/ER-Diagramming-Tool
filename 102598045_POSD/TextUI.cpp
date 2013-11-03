#include "TextUI.h"
#include <iostream>
#include <iomanip>
#include "Connector.h"
#include "Table.h"
#include "InstructionMenu.h"
#include "ApplicationSetting.h"
#include "StringUtil.h"
#include "StringSymbol.h"

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

void TextUI::alertException(string information){
    cout<<information<<endl;
}

void TextUI::notify(){
    TextUIPresenter* textUIPresenter = this->textPresentation->getTextUIPresenter();
    textUIPresenter->displayDiagram();
}