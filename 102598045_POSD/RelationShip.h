#pragma once

#include "Component.h"
#include "Node.h"
#include "Entity.h"
#include "RelationType.h"

class RelationShip : public Node{
public:
	RelationShip(ComponentData componentData);
	~RelationShip();

	string getType();
		
	int canConnectTo(Component* target);	
	bool hasSizeToConnect();

	bool isRelationType(string relationType);

	set<Entity*> getConnectedEntities();

	Component* clone() const;
};