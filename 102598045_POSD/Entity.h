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

	HashMap<string,Attribute*> getConnectedAttributes();
	Attribute* getAttributeByID(string id);
	HashMap<string,Attribute*> getPrimaryKeyAttributes();
	void setPrimaryKey(vector<string> primaryKeyIDVector);

	Component* clone() const;
};