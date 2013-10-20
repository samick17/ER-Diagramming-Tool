#pragma once

#include "Attribute.h"
#include <set>
#include "HashMap.h"

class Entity : public Node{
public:
	Entity(ComponentData componentData);
	~Entity();

	string toString();

	string getType();

	int canConnectTo(Component* target);

	HashMap<string,Attribute*> getConnectedAttributes();
	Attribute* getAttributeByID(string id);
	HashMap<string,Attribute*> getPrimaryKeyAttributes();
	void setPrimaryKey(set<string> primaryKeyIDSet);

	Component* clone() const;
};