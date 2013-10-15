#include "DeleteComponentCommand.h"
#include "FindComponentCommand.h"
#include "ERModelUtil.h"
#include "SetUtil.h"
#include "ComponentUtil.h"

DeleteComponentCommand :: DeleteComponentCommand(Presentation* presentation) : UnexecutableCommand(presentation){	
	this->component = NULL;
}

DeleteComponentCommand::~DeleteComponentCommand(){
	if(this->getExecutionFlag()){		
		//delete connectionSet
		SetUtil::deleteAllElementsInSet(this->connectionSet);
		//delete component	
		if(this->component != NULL){
			delete this->component;
			this->component = NULL;
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
	this->connectionSet = ERModelUtil::convertComponentSetToTypeSet<Connector>(this->component->getAllConnectors());		
	
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
		hash_map<string,ConnectionData*>::iterator connectionDataIterator;
		if((connectionDataIterator = this->connectionDataMap.find(connector->getID())) != this->connectionDataMap.end())	
			reConnectComponents(connectionDataIterator->second,connector);		
	}
	this->UnexecutableCommand::unExecute();
}

void DeleteComponentCommand::saveConnectionData(Connector* connector){
	Component* firstNode = connector->getFirstConnectedNode();
	Component* secondNode = connector->getSecondConnectedNode();		

	ConnectionData* connectionData = new ConnectionData(connector->getID(),firstNode->getID(),secondNode->getID());
	this->connectionDataMap.insert(ConnectionDataPair(connectionData->getConnectorID(),connectionData));
}

void DeleteComponentCommand::clearConnectionDataMap(){
	for each(ConnectionDataPair connectionDataPair in this->connectionDataMap){
		if(connectionDataPair.second != NULL){
			delete connectionDataPair.second;
			connectionDataPair.second = NULL;
		}
	}
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