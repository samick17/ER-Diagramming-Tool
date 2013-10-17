#pragma once

#include "Component.h"

class Connector : public Component{
	friend class ConnectorTest;	
public:
	Connector(ComponentData componentData);
	~Connector();

	string toString();

	string getType();

	void breakAllConnections();
	int canConnectTo(Component* target);
	bool hasSizeToConnect();

	Component* getFirstConnectedNode();
	Component* getSecondConnectedNode();
	bool isNodesConnection(Component* firstNode,Component* secondNode);

	Component* clone() const;
};