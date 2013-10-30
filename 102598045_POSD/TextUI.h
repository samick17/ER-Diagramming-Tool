#pragma once

#include "TextPresentation.h"

class Table;
class Connector;

class TextUI{
public:    
    TextUI(TextPresentation* textPresentation);
    ~TextUI();

    void displayMenu();
    void processCommand();

    void alertException(string infomation);
private:
    TextPresentation* textPresentation;
};