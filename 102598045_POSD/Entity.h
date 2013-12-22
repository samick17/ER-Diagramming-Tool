#pragma once

#include "Attribute.h"
#include <vector>
#include "HashMap.h"
#include "StringSymbol.h"

class Entity : public Node{
public:
    Entity(string componentID,string componentName = StringSymbol::Empty);
    ~Entity();

    int canConnectTo(Component* target);

    HashMap<string,Attribute*> getConnectedAttributes();
    Attribute* getAttributeByID(string id);
    HashMap<string,Attribute*> getPrimaryKeyAttributes();
    void setPrimaryKey(string componentID);

    void accept(ComponentVisitor* visitor);

    Component* clone() const;
};