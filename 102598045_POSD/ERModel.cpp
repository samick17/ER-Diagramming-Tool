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
	this->componentMap.put(component->getID(),component);
}
//erase component in componentMap, if contains key
void ERModel::eraseComponent(Component* component){
	if(component == NULL)
		throw NullPointerException();
	this->componentMap.remove(component->getID());
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

	try{
		return this->componentMap.get(id);
	}
	catch(Exception&){
		throw NoSuchNodeException(id);
	}	
}
//@return: firstNode & secondNode's connector
Connector* ERModel::getNodesConnector(Component* firstNode,Component* secondNode){
	if(firstNode == NULL || secondNode == NULL)
		throw NullPointerException();

	Connector* connection = NULL;
	if(this->componentMap.containsKey(firstNode->getID()) && 
		this->componentMap.containsKey(secondNode->getID())){
		HashMap<string,Connector*> connections = this->getAllConnectors();
		for each(Connector* connector in connections){
			if(connector->isNodesConnection(firstNode,secondNode)){
				connection = connector;
				return connection;
			}
		}
	}
	throw NullPointerException();
}

HashMap<string,Component*> ERModel::getAllComponents(){
	if(this->componentMap.empty())
		throw EmptyCollectionException(ComponentType::TypeComponent);
	
	return this->componentMap;
}

HashMap<string,Connector*> ERModel::getAllConnectors(){
	HashMap<string,Connector*> connectorMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->componentMap);

	if(connectorMap.empty()){
		throw EmptyCollectionException(ComponentType::TypeConnectorName);
	}

	return connectorMap;
}

HashMap<string,Entity*> ERModel::getAllEntities(){
	HashMap<string,Entity*> entitySet = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(this->getAllComponents());

	if(entitySet.empty()){
		throw EmptyCollectionException(ComponentType::TypeEntityName);
	}

	return entitySet;
}

HashMap<string,RelationShip*> ERModel::getAllRelationShips(){	
	HashMap<string,RelationShip*> relationShipSet = ERModelUtil::convertComponentHashMapToTypeHashMap<RelationShip>(this->getAllComponents());

	if(relationShipSet.empty()){
		throw EmptyCollectionException(ComponentType::TypeRelationShipName);
	}

	return relationShipSet;
}
//get All Tables
HashMap<string,Table*> ERModel::getAllTables(){
	try{
		return ERModelUtil::convertToTableMap(this->tableManager,this->getAllRelationShips());
	}catch(Exception&){
		throw EmptyCollectionException("Table");
	}
}
//clear all components & delete it
void ERModel::clearComponentMap(){
	ComponentFactory componentFactory;
	componentFactory.resetFactory();

	for each (Component* component in this->componentMap)
		delete component;
	
	this->componentMap.clear();
}