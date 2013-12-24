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
    ComponentVisitor(HashMap<string,string> reorderedIDMap);
    virtual ~ComponentVisitor();

    virtual void visit(Attribute* attribute) = 0;
    virtual void visit(Entity* entity) = 0;
    virtual void visit(RelationShip* relationShip) = 0;
    virtual void visit(Connector* connector) = 0;
protected:
    string getTransformedID(Component* component);
private:
    HashMap<string,string> reorderedIDMap;
};