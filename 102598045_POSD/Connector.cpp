#include "Connector.h"
#include "ERModel.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentUtil.h"
#include "ComponentConnectionSize.h"

Connector::Connector(ComponentData componentData) : Component(componentData){
}

Connector::~Connector(){
}

string Connector::toString(){
	string result = this->getID();
	result += " ";
	result += this->getFirstConnectedNode()->getID();
	result += ",";
	result += this->getSecondConnectedNode()->getID();

	return result;
}

string Connector::getType(){
	return ComponentType::TypeConnector;
}

void Connector::breakAllConnections(){
	Component* firstNode = this->getFirstConnectedNode();
	Component* secondNode = this->getSecondConnectedNode();

	ComponentUtil::disconnectWithEachOther(firstNode,secondNode,this);
}

int Connector::canConnectTo(Component* target){
	throw InvalidConnectException(this->getID(),target->getID());
}

bool Connector::hasSizeToConnect(){
	return this->getAllConnectors().size() < ComponentConnectionSize::ConnectorConnectionSize;
}

Component* Connector::getFirstConnectedNode(){		
	return (*this->getAllConnectors().begin());
}

Component* Connector::getSecondConnectedNode(){	
	return *(++this->getAllConnectors().begin());
}

bool Connector::isNodesConnection(Component* firstNode,Component* secondNode){	
	if(firstNode == secondNode)
		return false;

	bool isConnection = false;
	set<Component*> connections = this->getAllConnectors();

	isConnection = connections.find(firstNode) != connections.end();
	isConnection &= (connections.find(secondNode) != connections.end());

	return isConnection;
}

Component* Connector::clone() const
{ 
	return new Connector(*this); 
}