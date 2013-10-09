#include "DeleteComponentCommand.h"
#include "FindComponentCommand.h"
#include "ERModelUtil.h"
#include "SetUtil.h"
#include "ComponentUtil.h"

DeleteComponentCommand :: DeleteComponentCommand(Presentation* presentation) : UnexecutableCommand(presentation){	
	this->component = NULL;
	this->connectorFlag = false;
}

DeleteComponentCommand::~DeleteComponentCommand(){
	if(this->getExecutionFlag()){
		//delete component	
		if(this->component != NULL)
			delete this->component;
		//delete connectionSet
		SetUtil::deleteAllElementsInSet(this->connectionSet);
	}
	this->clearConnectionDataMap();
}

void DeleteComponentCommand :: execute(){
	if(this->component != NULL){
		this->clearConnectionDataMap();
		this->removeAndDisconnectComponents();
	}
	else 		
		this->doDeleteComponent();
	
	this->UnexecutableCommand::execute();
}

void DeleteComponentCommand::unExecute(){
	ERModel* erModel = this->presentation->getERModel();

	//add deleted Component to ERModel
	if(!this->connectorFlag)
		erModel->addComponent(this->component);

	for each(Connector* connector in this->connectionSet){
		//add connected Connector to ERModel
		erModel->addComponent(connector);
		//connect with each other
		hash_map<string,ConnectionData*>::iterator connectionDataIterator;
		if((connectionDataIterator = this->connectionDataMap.find(connector->getID())) != this->connectionDataMap.end())	
			reConnectComponents(connectionDataIterator->second,connector);		
	}
	this->UnexecutableCommand::unExecute();
}

void DeleteComponentCommand::clearConnectionDataMap(){
	for each(ConnectionDataPair connectionDataPair in this->connectionDataMap){
		if(connectionDataPair.second != NULL)
			delete connectionDataPair.second;
	}
	this->connectionDataMap.clear();
}
//remove component from ERModel
void DeleteComponentCommand::doDeleteComponent(){
	ERModel* erModel = this->presentation->getERModel();

	//find node to be connect
	FindComponentCommand findComponentCommand(this->presentation);
	findComponentCommand.setInfo("Please enter the component ID");
	findComponentCommand.execute();
	Component* find = findComponentCommand.getComponent();
	
	//save to variable - save deleted component
	this->component = find;
	//save to variable - save connected connections
	this->connectionSet = ERModelUtil::convertComponentSetToTypeSet<Connector>(find->getAllConnectors());		
	if(typeid(*this->component).name() == typeid(Connector).name()){
		this->connectionSet.insert(static_cast<Connector*>(this->component));
		this->connectorFlag = true;
	}

	this->removeAndDisconnectComponents();

	this->presentation->logMessage("The component '"+find->getID()+"' has been deleted. ",true);	
}
//remove component from ERMol & disconnect it
void DeleteComponentCommand::removeAndDisconnectComponents(){
	ERModel* erModel = this->presentation->getERModel();	

	//remove component from ERModel
	if(!this->connectorFlag)
		erModel->removeComponentByID(this->component->getID());
	
	Component* firstNode;
	Component* secondNode;
	//save connectionData & remove connectionSet from ERModel
	for each(Connector* connector in this->connectionSet){
		firstNode = connector->getFirstConnectedNode();
		secondNode = connector->getSecondConnectedNode();		

		ConnectionData* connectionData = new ConnectionData(connector->getID(),firstNode->getID(),secondNode->getID());
		this->connectionDataMap.insert(ConnectionDataPair(connectionData->getConnectorID(),connectionData));
		erModel->removeComponentByID(connector->getID());
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