#pragma once

#include <string>
#include <set>
#include "ComponentData.h"
#include "IClonable.h"
#include "NodeConnectionType.h"

using namespace std;

class Component : public IClonable{
public:
	Component(ComponentData componentData);
	virtual ~Component();

	virtual string toString();

	string getID();
	void setID(string id);
	virtual string getType();
	string getName();
	void setName(string);
	string getClassName();

	void connectTo(Component* target);	
	void disconnectTo(Component* target);
	virtual void breakAllConnections() = 0;
	virtual int canConnectTo(Component* target) = 0;
	virtual bool hasSizeToConnect();
	bool hasConnectedTo(Component* target);

	set<Component*> getAllConnectors();

	virtual Component* clone() const = 0;
protected:
	ComponentData componentData;
private:	
	set<Component*> connectionSet;
};