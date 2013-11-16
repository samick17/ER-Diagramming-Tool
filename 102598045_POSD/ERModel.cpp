#include "ERModel.h"
#include "ERModelUtil.h"
#include "TableUtil.h"
#include "ComponentUtil.h"
#include "ComponentFactory.h"
#include "CommandManager.h"
#include "NoSuchNodeException.h"
#include "NullPointerException.h"
#include "AddNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "ConnectNodeCommand.h"
#include "InputFileParser.h"
#include "OutputFileParser.h"

ERModel::ERModel(){
}

ERModel::~ERModel(){
    this->clearComponentMap();
}

Node* ERModel::addNode(string componentType){
    Node* node;
    ComponentFactory componentFactory;
    node = static_cast<Node*>(componentFactory.createComponent(componentType));
    this->commandManager.execute(new AddNodeCommand(this,node));
    return node;
}
//insert component in componentMap, if no such key
void ERModel::insertComponent(Component* component){
    string componentID = component->getID();
    if(!this->componentMap.containsKey(component->getID()))
        this->componentMap.put(component->getID(),component);
}
//insert component at index argument
void ERModel::insertComponentAt(Component* component,unsigned int index){
    string componentID = component->getID();
    if(!this->componentMap.containsKey(component->getID()))
        this->componentMap.insertAt(component->getID(),component,index);
}
//erase component in componentMap, if contains key
void ERModel::eraseComponent(Component* component){
    this->componentMap.remove(component->getID());
}

void ERModel::deleteComponent(Component* component){
    this->commandManager.execute(new DeleteComponentCommand(this,component));
}
//@return: NodeConnectionType
int ERModel::addConnection(Component* firstNode,Component* secondNode){
    int result = firstNode->canConnectTo(secondNode);

    if(result == NodeConnectionType::ValidConnect || result == NodeConnectionType::ConnectEntityAndRelation){
        ComponentFactory componentFactory;
        Connector* connector = static_cast<Connector*>(componentFactory.createComponent(ComponentType::TypeConnector));
        this->commandManager.execute(new ConnectNodeCommand(this,firstNode,secondNode,connector));
    }
    return result;
}

void ERModel::redo(){
    this->commandManager.redo();
    this->notify();
}

void ERModel::undo(){
    this->commandManager.undo();
    this->notify();
}

void ERModel::openFile(string filePath){
    InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(filePath,this);
    //open file should reset undo/redo state
    this->commandManager.popAllStack();
}

void ERModel::saveFile(string filePath){
    OutputFileParser outputFileParser = OutputFileParser(this->getAllComponents());
    outputFileParser.parseModelToFile(filePath);
}
//if doesn't contains such component, throw exception
Component* ERModel::getComponentByID(string id){
    if(this->componentMap.containsKey(id))
        return this->componentMap.get(id);
    throw NoSuchNodeException(id);
}
//@return: firstNode & secondNode's connector
Connector* ERModel::getNodesConnector(Component* firstNode,Component* secondNode){
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

HashMap<string,Component*>& ERModel::getAllComponents(){
    return this->componentMap;
}

HashMap<string,Attribute*> ERModel::getAllAttributes(){
    HashMap<string,Attribute*> attributeMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Attribute>(this->componentMap);
    return attributeMap;
}

HashMap<string,Connector*> ERModel::getAllConnectors(){
    HashMap<string,Connector*> connectorMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->componentMap);
    return connectorMap;
}

HashMap<string,Entity*> ERModel::getAllEntities(){
    HashMap<string,Entity*> entityMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(this->getAllComponents());
    return entityMap;
}

HashMap<string,RelationShip*> ERModel::getAllRelationShips(){
    HashMap<string,RelationShip*> relationShipMap = ERModelUtil::convertComponentHashMapToTypeHashMap<RelationShip>(this->getAllComponents());
    return relationShipMap;
}
//get All Tables
HashMap<string,Table*> ERModel::getAllTables(){
    return TableUtil::convertToTableMap(this->tableManager,this->getAllEntities(),this->getAllRelationShips());
}
//clear all components & delete it
void ERModel::clearComponentMap(){
    ComponentFactory componentFactory;
    componentFactory.resetFactory();
    this->commandManager.popAllStack();

    for each(Component*& component in this->componentMap){
		component = NULL;
		Component* componentBuffer = component;
		delete componentBuffer;
    }
    
    this->componentMap.clear();
}

void ERModel::registerSynchronizer(ISynchronizer* synchronizer){
    synchronizerVector.push_back(synchronizer);
}

void ERModel::unregisterSynchronizer(ISynchronizer* synchronizer){
    vector<ISynchronizer*>::iterator synchronizerIterator;
    synchronizerIterator = find(synchronizerVector.begin(),synchronizerVector.end(),synchronizer);
    synchronizerVector.erase(synchronizerIterator);
}

void ERModel::sync(string syncEventType){
    for each(ISynchronizer* synchronizer in this->synchronizerVector)
        synchronizer->sync(syncEventType);
}