#pragma once

#include "Attribute.h"
#include <set>

class Entity : public Node{
public:
	Entity(ComponentData componentData);
	~Entity();

	string toString();

	string getType();

	int canConnectTo(Component* target);
	bool hasSizeToConnect();

	set<Attribute*> getConnectedAttributes();
	Attribute* getAttributeByID(string id);
	set<Attribute*> getPrimaryKeyAttributes();
	void setPrimaryKey(set<string> primaryKeyIDSet);

	Component* clone() const;
};