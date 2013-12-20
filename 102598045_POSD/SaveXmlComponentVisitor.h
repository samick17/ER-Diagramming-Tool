#pragma once

#include "ComponentVisitor.h"

class SaveXmlComponentVisitor : public ComponentVisitor{
public:
    SaveXmlComponentVisitor();
    ~SaveXmlComponentVisitor();

    void visit(Attribute* attribute);
    void visit(Entity* entity);
    void visit(RelationShip* relationShip);
    void visit(Connector* connector);
};