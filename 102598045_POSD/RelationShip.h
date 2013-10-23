#pragma once

#include "Component.h"
#include "Node.h"
#include "Entity.h"
#include "RelationType.h"
#include "HashMap.h"

class RelationShip : public Node{
public:
	RelationShip(ComponentData componentData);
	~RelationShip();

	string getType();
		
	int canConnectTo(Component* target);	
	bool hasSizeToConnect();
	bool isRelationType(string relationType);

	HashMap<string,Entity*> getConnectedEntities();

	Component* clone() const;
};