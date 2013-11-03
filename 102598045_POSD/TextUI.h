#pragma once

#include "TextPresentation.h"
#include "IObserver.h"

class Table;
class Connector;

class TextUI : public IObserver{
public:    
    TextUI(TextPresentation* textPresentation);
    ~TextUI();

    void displayMenu();
    void processCommand();

    void notify();
private:
    TextPresentation* textPresentation;
};