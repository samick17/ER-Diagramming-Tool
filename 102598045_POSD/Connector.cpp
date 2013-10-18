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
//format:id firstConnectedNode,secondConnectedNode
string Connector::toString(){
	string result = this->getID();
	result += " ";
	result += this->getFirstConnectedNode()->getID();
	this->getFirstConnectedNode()->getName();
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
	return this->getAllConnections().size() < ComponentConnectionSize::ConnectorConnectionSize;
}
//first node's id will always less than second node
Component* Connector::getFirstConnectedNode(){
	Component* firstNode = this->getAllConnections().getValueByIndex(0);
	Component* secondNode = this->getAllConnections().getValueByIndex(1);
	if(strcmp(firstNode->getID().c_str(),secondNode->getID().c_str())>0){
		return secondNode;
	}
	return firstNode;
}
//second node's id will always greater than first node
Component* Connector::getSecondConnectedNode(){
	Component* firstNode = this->getAllConnections().getValueByIndex(0);
	Component* secondNode = this->getAllConnections().getValueByIndex(1);
	if(strcmp(firstNode->getID().c_str(),secondNode->getID().c_str())>0){
		return firstNode;
	}
	return secondNode;
}

bool Connector::isNodesConnection(Component* firstNode,Component* secondNode){	
	if(firstNode == secondNode)
		return false;
	if(firstNode == NULL || secondNode == NULL)
		return false;

	bool isConnection = false;
	HashMap<string,Component*> connections = this->getAllConnections();

	isConnection = connections.containsKey(firstNode->getID());
	isConnection &= connections.containsKey(secondNode->getID());

	return isConnection;
}

Component* Connector::clone() const
{ 
	return new Connector(*this); 
}