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
private:
    Presentation* presentation;
    GraphicalUI* graphicalUI;
};