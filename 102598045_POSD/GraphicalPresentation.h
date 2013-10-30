#pragma once

#include "Component.h"
#include "Presentation.h"

class GraphicalUI;

class GraphicalPresentation{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    void openFile();
    void saveFile();
    void close();

    void displayDiagram();
    void displayTable();
    void displayComponents();
    void displayConnections();
    void displayEntities();
    void displayEntityAttributes(Entity* entity);

    void setGraphicalUI(GraphicalUI* graphicalUI);
private:    
    Presentation* presentation;
    GraphicalUI* graphicalUI;
};