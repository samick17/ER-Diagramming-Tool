#pragma once

#include "TextPresentation.h"

class TextUIPresenter{
public:
    TextUIPresenter(TextPresentation* textPresentation);
    ~TextUIPresenter();

    void displayTitle(string title);
    void displayMenu();
    void displayTable();
    void displayComponents();
    void displayConnections();
    void displayEntities();
    void displayEntityAttributes(Entity* entity);
    void displayDiagram();
    void logMessage(string message,bool endWithLine);
private:
    void displayComponentMap(HashMap<string,Component*> componentMap);
    TextPresentation* textPresentation;
};