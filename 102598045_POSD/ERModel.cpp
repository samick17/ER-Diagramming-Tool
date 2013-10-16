#include "ERModel.h"
#include "ComponentFactory.h"
#include "ERModelUtil.h"
#include <algorithm>
#include "NoSuchNodeException.h"
#include "NullPointerException.h"
#include "ComponentUtil.h"

ERModel::ERModel(){	
}

ERModel::~ERModel(){
	this->clearComponentMap();
}

Component* ERModel::addNode(string componentType){
	Component* node;
	ComponentFactory componentFactory;
			
	node = componentFactory.createComponent(componentType);
	this->insertComponent(node);

	return node;
}
//insert component in componentMap, if no such key
void ERModel::insertComponent(Component* component){
	if(component == NULL)
		throw NullPointerException();
	string componentID = component->getID();
	if(this->componentMap.find(componentID) == this->componentMap.end()){
		this->componentMap.insert(ComponentPair(componentID,component));	
		//in order to keep component order, use a vector to convert component key to vector
		this->componentKeyOrderVector.push_back(componentID);
	}
}
//erase component in componentMap, if contains key
void ERModel::eraseComponent(Component* component){
	if(component == NULL)
		throw NullPointerException();
	if(this->componentMap.find(component->getID()) != this->componentMap.end()){
		this->componentMap.erase(component->getID());
		//in order to keep component order, use a vector to convert component key to vector	
		vector<string>::iterator index = find(this->componentKeyOrderVector.begin(),this->componentKeyOrderVector.end(),component->getID());
		if (index != this->componentKeyOrderVector.end()) 
			this->componentKeyOrderVector.erase(index);
	}
}
//@return: NodeConnectionType
int ERModel::addConnection(Component* firstNode,Component* secondNode){
	if(firstNode == NULL || secondNode == NULL)
		throw NullPointerException();
	int result = firstNode->canConnectTo(secondNode);

	if(result == NodeConnectionType::ValidConnect || result == NodeConnectionType::ConnectEntityAndRelation){
		Component* connector = this->addNode(ComponentType::TypeConnector);
		ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
	}
	return result;
}
//if doesn't contains such component, throw exception
Component* ERModel::getComponentByID(string id){
	unordered_map<string,Component*>::const_iterator find;

	if((find = this->componentMap.find(id)) != this->componentMap.end())	
		return find->second;

	throw NoSuchNodeException(id);
}
//@return: firstNode & secondNode's connector
Connector* ERModel::getNodesConnector(Component* firstNode,Component* secondNode){
	if(firstNode == NULL || secondNode == NULL)
		throw NullPointerException();

	Connector* connection = NULL;
	if(this->componentMap.find(firstNode->getID()) != this->componentMap.end() && 
		this->componentMap.find(secondNode->getID()) != this->componentMap.end()){
		set<Connector*> connections = this->getAllConnectors();
		for each(Connector* connector in connections){
			if(connector->isNodesConnection(firstNode,secondNode)){
				connection = connector;
				return connection;
			}
		}
	}
	throw NullPointerException();
}

set<Component*> ERModel::getAllComponents(){
	if(this->componentMap.empty())
		throw EmptyCollectionException(ComponentType::TypeComponent);

	set<Component*> componentSet;

	for each(ComponentPair componentPair in this->componentMap)	
		componentSet.insert(componentPair.second);
	
	return componentSet;
}

set<Connector*> ERModel::getAllConnectors(){
	return ERModelUtil::convertComponentSetToTypeSet<Connector>(this->getAllComponents());
}

set<Entity*> ERModel::getAllEntities(){
	return ERModelUtil::convertComponentSetToTypeSet<Entity>(this->getAllComponents());
}

set<RelationShip*> ERModel::getAllRelationShips(){	
	return ERModelUtil::convertComponentSetToTypeSet<RelationShip>(this->getAllComponents());
}
//get All Tables
set<Table*> ERModel::getAllTables(){
	return ERModelUtil::convertToTableSet(this->tableManager,this->getAllRelationShips());
}
//clear all components & delete it
void ERModel::clearComponentMap(){
	ComponentFactory componentFactory;
	componentFactory.resetFactory();

	for each (ComponentPair componentPair in this->componentMap)	{
		delete componentPair.second;
		componentPair.second = NULL;
	}
	
	this->componentMap.clear();
	this->componentKeyOrderVector.clear();
}
//get component ordered ID Vector
vector<string> ERModel::getComponentKeyOrderVector() const
{
	return this->componentKeyOrderVector;
}