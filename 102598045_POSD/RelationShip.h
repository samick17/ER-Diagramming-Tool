#pragma once

#include "Component.h"
#include "Node.h"
#include "Entity.h"
#include "RelationType.h"
#include "HashMap.h"
#include "StringSymbol.h"

class RelationShip : public Node{
public:
    RelationShip(string componentID,string componentName = StringSymbol::Empty);
    ~RelationShip();
        
    int canConnectTo(Component* target);
    bool hasSizeToConnect();
    bool isRelationType(string relationType);

    HashMap<string,Entity*> getConnectedEntities();
};