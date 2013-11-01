#pragma once

#include "Component.h"
#include "Presentation.h"

class GraphicalUI;
/*class Attribute;
class Entity;
class RelationShip;
class Connector;*/

class GraphicalPresentation{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    HashMap<string,Attribute*> getAllAttributes();
    HashMap<string,Entity*> getAllEntities();
    HashMap<string,RelationShip*> getAllRelationShips();
    HashMap<string,Connector*> getAllConnectors();

    void openFile();
    void saveFile();
    void close();
private:
    Presentation* presentation;
    GraphicalUI* graphicalUI;
};