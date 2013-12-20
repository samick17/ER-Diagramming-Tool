#pragma once

#include "ComponentVisitor.h"
#include "Document.h"

class SaveComponentVisitor : public ComponentVisitor{
public:
    SaveComponentVisitor();
    ~SaveComponentVisitor();

    void visit(Attribute* attribute);
    void visit(Entity* entity);
    void visit(RelationShip* relationShip);
    void visit(Connector* connector);
};