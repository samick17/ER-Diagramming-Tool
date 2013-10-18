#pragma once

#include <string>
#include <set>
#include "HashMap.h"
#include "ComponentData.h"
#include "IClonable.h"
#include "NodeConnectionType.h"
#include <gtest/gtest_prod.h> 

using namespace std;

class Component : public IClonable{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest,addConnection);
	friend class ConnectorTest;
	FRIEND_TEST(ConnectorTest,testBreakAllConnections);
	FRIEND_TEST(ConnectorTest,testClone);
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

	HashMap<string,Component*> getAllConnections();

	virtual Component* clone() const = 0;
protected:
	ComponentData componentData;
private:	
	HashMap<string,Component*> connectionMap;
};