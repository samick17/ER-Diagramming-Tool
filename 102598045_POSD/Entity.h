#pragma once

#include "Attribute.h"
#include <vector>
#include "HashMap.h"

class Entity : public Node{
public:
    Entity(string componentID);
    ~Entity();

    int canConnectTo(Component* target);

    HashMap<string,Attribute*> getConnectedAttributes();
    Attribute* getAttributeByID(string id);
    HashMap<string,Attribute*> getPrimaryKeyAttributes();
    void setPrimaryKey(vector<string> primaryKeyIDVector);
};