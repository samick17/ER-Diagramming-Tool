#pragma once

#include "Attribute.h"
#include <vector>
#include "HashMap.h"

class Entity : public Node{
public:
	Entity(ComponentData componentData);
	~Entity();

	string toString();

	string getType();

	int canConnectTo(Component* target);
	bool hasSizeToConnect();

	HashMap<string,Attribute*> getConnectedAttributes();
	Attribute* getAttributeByID(string id);
	HashMap<string,Attribute*> getPrimaryKeyAttributes();
	void setPrimaryKey(set<string> primaryKeyIDSet);

	Component* clone() const;
};