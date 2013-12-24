#pragma once

#include <string>
#include "HashMap.h"
#include <gtest/gtest_prod.h>

class Attribute;
class Entity;
class RelationShip;
class Connector;
class Component;

using namespace std;

class ComponentVisitor{
public:
    ComponentVisitor();
    virtual ~ComponentVisitor();

    void visit(Attribute* attribute);
    void visit(Entity* entity);
    void visit(RelationShip* relationShip);
    void visit(Connector* connector);
protected:
    string getTransformedID(Component* component);
    virtual void doVisit(Attribute* attribute) = 0;
    virtual void doVisit(Entity* entity) = 0;
    virtual void doVisit(RelationShip* relationShip) = 0;
    virtual void doVisit(Connector* connector) = 0;
private:
    void preVisit(Component* component);
    HashMap<string,string> reorderedIDMap;
    int currentVisitIndex;
};