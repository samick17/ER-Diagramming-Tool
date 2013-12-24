#pragma once

#include "ComponentVisitor.h"

class SaveXmlComponentVisitor : public ComponentVisitor{
public:
    SaveXmlComponentVisitor();
    ~SaveXmlComponentVisitor();

protected:
    void doVisit(Attribute* attribute);
    void doVisit(Entity* entity);
    void doVisit(RelationShip* relationShip);
    void doVisit(Connector* connector);
};