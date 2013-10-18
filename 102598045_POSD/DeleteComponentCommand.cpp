#include "DeleteComponentCommand.h"
#include "FindComponentCommand.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"

DeleteComponentCommand :: DeleteComponentCommand(Presentation* presentation) : UnexecutableCommand(presentation){	
	this->component = NULL;
}

DeleteComponentCommand::~DeleteComponentCommand(){
	if(this->getExecutionFlag()){		
		//delete connectionSet		
		for each(Connector* connector in this->connectionSet)
			delete connector;
		//delete component	
		if(this->component != NULL){
			delete this->component;
		}
	}
	this->clearConnectionDataMap();
}

void DeleteComponentCommand::setupCommand(){
	//find node to be connect
	FindComponentCommand findComponentCommand(this->presentation);
	findComponentCommand.setInfo("Please enter the component ID");
	findComponentCommand.execute();	
	
	//save to variable - save deleted component
	this->component = findComponentCommand.getComponent();
	//save to variable - save connected connections
	this->connectionSet = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->component->getAllConnections());		
	
	this->removeAndDisconnectComponents();

	this->presentation->logMessage("The component '"+this->component->getID()+"' has been deleted. ",true);	
}

void DeleteComponentCommand :: execute(){
	ERModel* erModel = this->presentation->getERModel();

	try{
		erModel->getComponentByID(this->component->getID());

		this->clearConnectionDataMap();
		this->removeAndDisconnectComponents();
	}
	catch(Exception&){
	}
	
	this->UnexecutableCommand::execute();
}

void DeleteComponentCommand::unExecute(){
	ERModel* erModel = this->presentation->getERModel();

	//add deleted Component to ERModel
	erModel->insertComponent(this->component);

	for each(Connector* connector in this->connectionSet){
		//add connected Connector to ERModel
		erModel->insertComponent(connector);
		//connect with each other
		if(this->connectionDataMap.containsKey(connector->getID()))
			reConnectComponents(this->connectionDataMap.get(connector->getID()),connector);
	}
	this->UnexecutableCommand::unExecute();
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
}
//remove component from ERMol & disconnect it
void DeleteComponentCommand::removeAndDisconnectComponents(){
	ERModel* erModel = this->presentation->getERModel();	

	//remove component from ERModel	
	if(typeid(*this->component).name() == typeid(Connector).name()){
		Connector* connector = static_cast<Connector*>(this->component);
		this->saveConnectionData(connector);		
	}
	erModel->eraseComponent(this->component);
	
	//save connectionData & remove connectionSet from ERModel
	for each(Connector* connector in this->connectionSet){
		saveConnectionData(connector);
		erModel->eraseComponent(connector);
	}
	//break connections
	this->component->breakAllConnections();
}
//undo - reconnect this component & related connector
void DeleteComponentCommand::reConnectComponents(ConnectionData* connectionData,Connector* connector)
{
	ERModel* erModel = this->presentation->getERModel();
	Component* firstNode = erModel->getComponentByID(connectionData->getConnectedFirstNodeID());
	Component* secondNode = erModel->getComponentByID(connectionData->getConnectedSecondNodeID());

	//connect with each other
	ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
}