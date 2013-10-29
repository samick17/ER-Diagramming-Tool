#include "TextUIProcess.h"

TextUIProcess::TextUIProcess(TextUI* textUI) : textUI(textUI){
}

TextUIProcess::~TextUIProcess(){
}

void TextUIProcess::run(){
    while(true){
        this->textUI->displayMenu();
        this->textUI->processCommand();
    }
}