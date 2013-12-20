#include "TextUIProcess.h"

TextUIProcess::TextUIProcess(TextUI* textUI) : textUI(textUI){
    this->start();
}

TextUIProcess::~TextUIProcess(){
}

void TextUIProcess::run(){
    while(true){
        this->textUI->displayMenu();
        this->textUI->processCommand();
        sleep(SLEEP_TIME);
    }
}