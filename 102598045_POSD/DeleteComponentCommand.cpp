#include "DeleteComponentCommand.h"
#include "ERModel.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"

DeleteComponentCommand::DeleteComponentCommand(ERModel* erModel,Component* component) : erModel(erModel),component(component){
}

DeleteComponentCommand::~DeleteComponentCommand(){
	if(this->executionFlag){
        //delete connectionSet
        for each(Connector* connector in this->connectionMap)
            delete connector;
        //delete component    
        if(this->component != NULL)
            delete this->component;
    }
    this->clearConnectionDataMap();
}
void DeleteComponentCommand::execute(){
    this->clearConnectionDataMap();
    this->removeAndDisconnectComponents();
    this->executionFlag = true;
}

void DeleteComponentCommand::unExecute(){
    //insert All connectors to ERModel at origin index
    for(HashMap<string,Connector*>::reverse_iterator connectorIterator = this->connectionMap.rbegin(); connectorIterator!= this->connectionMap.rend(); connectorIterator++){
        Connector* connector = *connectorIterator;
        this->erModel->insertComponentAt(connector,this->componentIndexMap.get(connector->getID()));
    }
    //insert Component to ERModel at origin index
    this->erModel->insertComponentAt(this->component,this->componentIndexMap.get(this->component->getID()));
    //reconnect all
    for each(Connector* connector in this->connectionMap){        
        reConnectComponents(this->connectionDataMap.get(connector->getID()),connector);
    }
    if(typeid(*this->component).name() == typeid(Connector).name())
        reConnectComponents(this->connectionDataMap.get(this->component->getID()),static_cast<Connector*>(component));

	this->executionFlag = false;
}

void DeleteComponentCommand::saveConnectionData(Connector* connector){
    Component* firstNode = connector->getFirstConnectedNode();
    Component* secondNode = connector->getSecondConnectedNode();

    ConnectionData* connectionData = new ConnectionData(connector->getID(),firstNode->getID(),secondNode->getID());
    this->connectionDataMap.put(connectionData->getConnectorID(),connectionData);
}

void DeleteComponentCommand::clearConnectionDataMap(){
    for each(ConnectionData* connectionData in this->connectionDataMap)
        delete connectionData;
    this->connectionDataMap.clear();
    this->componentIndexMap.clear();
}
//remove component from ERMol & disconnect it
void DeleteComponentCommand::removeAndDisconnectComponents(){
    //save to variable - save connected connections
    this->connectionMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->component->getAllConnections());
    //if is connector,save to connection data
    if(typeid(*this->component).name() == typeid(Connector).name())
        this->saveConnectionData(static_cast<Connector*>(this->component));
    //save index & remove component from ERModel
    componentIndexMap.put(this->component->getID(),this->erModel->getAllComponents().getValueIndex(this->component));
    this-> erModel->eraseComponent(this->component);

    //save connectionData & remove connectionSet from ERModel
    for each(Connector* connector in this->connectionMap){
        saveConnectionData(connector);
        //save index & remove connector from ERModel
        componentIndexMap.put(connector->getID(),this->erModel->getAllComponents().getValueIndex(connector));
        this->erModel->eraseComponent(connector);
    }
    //break connections
    this->component->breakAllConnections();
}
//undo - reconnect this component & related connector
void DeleteComponentCommand::reConnectComponents(ConnectionData* connectionData,Connector* connector){
    Component* firstNode = this->erModel->getComponentByID(connectionData->getConnectedFirstNodeID());
    Component* secondNode = this->erModel->getComponentByID(connectionData->getConnectedSecondNodeID());
    //connect with each other
    ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
}