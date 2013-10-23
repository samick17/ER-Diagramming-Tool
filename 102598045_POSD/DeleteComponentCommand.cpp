#include "DeleteComponentCommand.h"
#include "FindComponentCommand.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"

DeleteComponentCommand::DeleteComponentCommand(Presentation* presentation) : UnexecutableCommand(presentation){	
	this->component = NULL;
}

DeleteComponentCommand::~DeleteComponentCommand(){
	if(this->getExecutionFlag()){		
		//delete connectionSet		
		for each(Connector* connector in this->connectionMap)
			delete connector;
		//delete component	
		if(this->component != NULL)
			delete this->component;		
	}
	this->clearConnectionDataMap();
}
/**Non testable function**/
void DeleteComponentCommand::setupCommand(){
	//find node to be connect
	FindComponentCommand findComponentCommand(this->presentation);
	findComponentCommand.setInfo("Please enter the component ID");
	findComponentCommand.execute();	
	
	//save to variable - save deleted component
	this->component = findComponentCommand.getComponent();	
	this->removeAndDisconnectComponents();

	this->presentation->logMessage("The component '"+this->component->getID()+"' has been deleted. ",true);	
}

void DeleteComponentCommand::execute(){
	if(this->getExecutionFlag())
		return;
	ERModel* erModel = this->presentation->getERModel();

	if(erModel->getAllComponents().containsKey(this->component->getID())){
		erModel->getComponentByID(this->component->getID());

		this->clearConnectionDataMap();
		this->removeAndDisconnectComponents();
	}	
	
	this->UnexecutableCommand::execute();
}

void DeleteComponentCommand::unExecute(){
	if(!this->getExecutionFlag())
		return;	
	ERModel* erModel = this->presentation->getERModel();	
	//insert All connectors to ERModel at origin index
	for(HashMap<string,Connector*>::reverse_iterator connectorIterator = this->connectionMap.rbegin(); connectorIterator!= this->connectionMap.rend(); connectorIterator++){
		Connector* connector = *connectorIterator;		
		erModel->insertComponentAt(connector,this->componentIndexMap.get(connector->getID()));
	}
    //insert Component to ERModel at origin index
	erModel->insertComponentAt(this->component,this->componentIndexMap.get(this->component->getID()));
	//reconnect all
	for each(Connector* connector in this->connectionMap){		
		reConnectComponents(this->connectionDataMap.get(connector->getID()),connector);
	}
	if(typeid(*this->component).name() == typeid(Connector).name())
		reConnectComponents(this->connectionDataMap.get(this->component->getID()),static_cast<Connector*>(component));

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
	this->componentIndexMap.clear();
}
//remove component from ERMol & disconnect it
void DeleteComponentCommand::removeAndDisconnectComponents(){
	ERModel* erModel = this->presentation->getERModel();	
	//save to variable - save connected connections
	this->connectionMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->component->getAllConnections());
	//if is connector,save to connection data
	if(typeid(*this->component).name() == typeid(Connector).name())
		this->saveConnectionData(static_cast<Connector*>(this->component));	
	//save index & remove component from ERModel
	componentIndexMap.put(this->component->getID(),erModel->getAllComponents().getValueIndex(this->component));
	erModel->eraseComponent(this->component);
	
	//save connectionData & remove connectionSet from ERModel
	for each(Connector* connector in this->connectionMap){
		saveConnectionData(connector);
		//save index & remove connector from ERModel
		componentIndexMap.put(connector->getID(),erModel->getAllComponents().getValueIndex(connector));
		erModel->eraseComponent(connector);
	}
	//break connections
	this->component->breakAllConnections();
}
//undo - reconnect this component & related connector
void DeleteComponentCommand::reConnectComponents(ConnectionData* connectionData,Connector* connector){
	ERModel* erModel = this->presentation->getERModel();
	Component* firstNode = erModel->getComponentByID(connectionData->getConnectedFirstNodeID());
	Component* secondNode = erModel->getComponentByID(connectionData->getConnectedSecondNodeID());

	//connect with each other
	ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
}