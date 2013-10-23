#include "ComponentUtil.h"
#include "NoSuchNodeException.h"

void ComponentUtil::connectWithEachOther(Component* firstNode,Component* secondNode,Component* connector){
	firstNode->connectTo(connector);
	secondNode->connectTo(connector);
	connector->connectTo(firstNode);
	connector->connectTo(secondNode);
}

void ComponentUtil::disconnectWithEachOther(Component* firstNode,Component* secondNode,Component* connector){
	firstNode->disconnectTo(connector);
	secondNode->disconnectTo(connector);
	connector->disconnectTo(firstNode);
	connector->disconnectTo(secondNode);
}