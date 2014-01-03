#include "DeleteComponentCommand.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"
#include "HashMapUtil.h"
#include "Attribute.h"

DeleteComponentCommand::DeleteComponentCommand(HashMap<string,Component*>& componentMap,Component* component) : componentMap(componentMap),component(component){
}

DeleteComponentCommand::~DeleteComponentCommand(){
    if(this->getExecutionFalg()){
        //delete connectionSet
        HashMapUtil::deleteAll(this->connectionMap);
        //delete component
        if(this->component)
            delete this->component;
    }
    this->clearConnectionDataMap();
}

void DeleteComponentCommand::doExecute(){
    this->clearConnectionDataMap();
    this->attributePrimaryKeyMap.clear();
    this->removeAndDisconnectComponents();
}

void DeleteComponentCommand::doUnExecute(){
    //insert All connectors to ERModel at origin index
    for(auto connectorIterator = this->connectionMap.rbegin(); connectorIterator!= this->connectionMap.rend(); connectorIterator++){
        Connector* connector = *connectorIterator;
        this->componentMap.insertAt(connector->getID(),connector,this->componentIndexMap.get(connector->getID()));
    }
    //insert Component to ERModel at origin index
    this->componentMap.insertAt(this->component->getID(),this->component,this->componentIndexMap.get(this->component->getID()));
    //reconnect all
    for each(Connector* connector in this->connectionMap)
        reConnectComponents(this->connectionDataMap.get(connector->getID()),connector);
    for each(Attribute* attribute in this->attributePrimaryKeyMap)
        attribute->setAsPrimaryKey();
    if(this->component->isTypeOf<Connector>())
        reConnectComponents(this->connectionDataMap.get(this->component->getID()),static_cast<Connector*>(component));
}

void DeleteComponentCommand::saveConnectionData(Connector* connector){
    Component* firstNode = connector->getFirstConnectedNode();
    Component* secondNode = connector->getSecondConnectedNode();

    ConnectionData* connectionData = new ConnectionData(connector->getID(),firstNode->getID(),secondNode->getID());
    this->connectionDataMap.put(connectionData->getConnectorID(),connectionData);
}

void DeleteComponentCommand::saveAttributeKeyAndSetAsDefaultKey(HashMap<string,Attribute*> connectedAttributeMap){
    for each(Attribute* attribute in connectedAttributeMap){
        string attributeID = attribute->getID();
        if(attribute->isPrimaryKey() && !this->attributePrimaryKeyMap.containsKey(attributeID)){
            this->attributePrimaryKeyMap.put(attributeID,attribute);
            attribute->setAsDefaultKey();
        }
    }
}

void DeleteComponentCommand::clearConnectionDataMap(){
    HashMapUtil::deleteAll(this->connectionDataMap);
    this->componentIndexMap.clear();
}
//remove component from ERMol & disconnect it
void DeleteComponentCommand::removeAndDisconnectComponents(){
    //save to variable - save connected connections
    this->connectionMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->component->getAllConnections());
    //if is connector,save to connection data
    if(this->component->isTypeOf<Connector>()){
        this->saveConnectionData(static_cast<Connector*>(this->component));
        this->saveAttributeKeyAndSetAsDefaultKey(ERModelUtil::convertComponentHashMapToTypeHashMap<Attribute>(this->component->getAllConnections()));
    }
    //save index & remove component from ERModel
    componentIndexMap.put(this->component->getID(),this->componentMap.getValueIndex(this->component));
    this-> componentMap.remove(this->component->getID());
    //save connectionData & remove connectionSet from ERModel
    for each(Connector* connector in this->connectionMap){
        this->saveConnectionData(connector);
        this->saveAttributeKeyAndSetAsDefaultKey(ERModelUtil::convertComponentHashMapToTypeHashMap<Attribute>(connector->getAllConnections()));
        //save index & remove connector from ERModel
        componentIndexMap.put(connector->getID(),this->componentMap.getValueIndex(connector));
        this->componentMap.remove(connector->getID());
    }
    //break connections
    this->component->breakAllConnections();
}
//undo - reconnect this component & related connector
void DeleteComponentCommand::reConnectComponents(ConnectionData* connectionData,Connector* connector){
    Component* firstNode = this->componentMap.get(connectionData->getConnectedFirstNodeID());
    Component* secondNode = this->componentMap.get(connectionData->getConnectedSecondNodeID());
    //connect with each other
    ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
}