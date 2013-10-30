#include "TextUIProcess.h"


TextUIProcess::TextUIProcess(TextUI* textUI) : textUI(textUI){
	this->stopRequested = false;
    this->start();
}

TextUIProcess::~TextUIProcess(){

}

void TextUIProcess::requestStop(){
    this->mutex.lock();
    this->stopRequested = true;
    this->mutex.unlock();
    this->wait();
}

void TextUIProcess::run(){
    while(!stopRequested){
        this->textUI->displayMenu();
        this->textUI->processCommand();
    }
}