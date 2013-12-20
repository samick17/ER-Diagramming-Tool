#pragma once

#include <gtest/gtest_prod.h>

class Attribute;
class Entity;
class RelationShip;
class Connector;

class ComponentVisitor{
public:
    ComponentVisitor();
    virtual ~ComponentVisitor();

    virtual void visit(Attribute* attribute) = 0;
    virtual void visit(Entity* entity) = 0;
    virtual void visit(RelationShip* relationShip) = 0;
    virtual void visit(Connector* connector) = 0;
};