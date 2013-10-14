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

	return node;
}

void ERModel::removeComponentByID(string id){
	Component* find = this->getComponentByID(id);
	this->eraseComponent(find);
}
//@return: NodeConnectionType
int ERModel::addConnection(Component* firstNode,Component* secondNode){
	int result = firstNode->canConnectTo(secondNode);

	if(result == NodeConnectionType::ValidConnect || result == NodeConnectionType::ConnectEntityAndRelation){
		Component* connector = this->addNode(ComponentType::TypeConnector);
		this->insertComponent(connector);
		ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
	}
	return result;
}

Component* ERModel::getComponentByID(string id){
	unordered_map<string,Component*>::const_iterator find;

	if((find = this->componentMap.find(id)) != this->componentMap.end())	
		return find->second;

	throw NoSuchNodeException(id);
}
//@return: firstNode & secondNode's connector
Connector* ERModel::getNodesConnector(Component* firstNode,Component* secondNode){
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
//insert component in componentMap
void ERModel::insertComponent(Component* component){
	if(component == NULL)
		return;
	this->componentMap.insert(ComponentPair(component->getID(),component));	
	//in order to keep component order, use a vector to convert component key to vector
	this->componentKeyOrderVector.push_back(component->getID());
}
//erase component in componentMap
void ERModel::eraseComponent(Component* component){
	this->componentMap.erase(component->getID());	
	//in order to keep component order, use a vector to convert component key to vector	
	vector<string>::iterator index = find(this->componentKeyOrderVector.begin(),this->componentKeyOrderVector.end(),component->getID());
	if (index != this->componentKeyOrderVector.end()) 
    this->componentKeyOrderVector.erase(index);
}