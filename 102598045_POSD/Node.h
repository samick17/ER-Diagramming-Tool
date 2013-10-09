#pragma once

#include "Component.h"

class Node : public Component{
public:
	Node(ComponentData componentData);
	~Node();

	string getType();

	void breakAllConnections();
	bool hasSizeToConnect();

	int canConnectTo(Component* target);

	Component* clone() const = 0;
};