#include "LoadFileCommand.h"
#include "CommandManager.h"
#include "Document.h"
#include "StringUtil.h"
#include "ComponentType.h"
#include "VectorUtil.h"
#include "DisplayDiagramCommand.h"

LoadFileCommand :: LoadFileCommand(Presentation* presentation) : Command(presentation){	
}

LoadFileCommand::~LoadFileCommand(){
}

void LoadFileCommand :: execute(){
	this->presentation->logMessage("Please input the file name: ",true);
	string filePath = this->presentation->getInput();

	Document doc(filePath);
	doc.openFile();

	//load all Nodes & Connectors
	this->loadAllComponentsFromDoc(doc);
	this->loadAllConnectorsFromDoc(doc);
	this->addAllComponentToERModel();
	//load all Primary Key
	this->loadAllPrimaryKeyFromDoc(doc);

	//load file succeed. pop all stack in commandManager
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->popAllStack();
	//display current diagram
	DisplayDiagramCommand displayDiagramCommand(this->presentation);
	displayDiagramCommand.execute();	
}

void LoadFileCommand::unExecute(){
}

void LoadFileCommand::loadAllComponentsFromDoc(Document& doc){
	ERModel* erModel = this->presentation->getERModel();
	erModel->clearComponentMap();

	string line;
	while((line = doc.readLine()) != ""){
		//load component data & push to componentDataQueue
		vector<string> componentDataVector = StringUtil::split(line,',');
		string type = StringUtil::trim(componentDataVector[0]);
		string name = "";

		//load component name
		if(componentDataVector.size() > 1)		
			name = StringUtil::trim(componentDataVector[1]);

		this->componentDataQueue.push(StringPair(type,name));		
	}
}

void LoadFileCommand::loadAllConnectorsFromDoc(Document& doc){
	string line;
	while((line = doc.readLine()) != ""){
		//load connection data & push to connectionDataQueue
		vector<string> connectorDataVector = StringUtil::split(line,' ');
		vector<string> connectorNodeIDVector = StringUtil::split(connectorDataVector[1],',');

		string connectorID = StringUtil::trim(connectorDataVector[0]);
		string firstNodeID = StringUtil::trim(connectorNodeIDVector[0]);
		string secondNodeID = StringUtil::trim(connectorNodeIDVector[1]);

		ConnectionData connectionData(connectorID,firstNodeID,secondNodeID);

		this->connectionDataQueue.push(connectionData);
	}
}

void LoadFileCommand::loadAllPrimaryKeyFromDoc(Document& doc){
	ERModel* erModel = this->presentation->getERModel();

	string line;
	while((line = doc.readLine()) != ""){
		vector<string> entitysPrimaryKeyVector = StringUtil::split(line,' ');
		string entityID = entitysPrimaryKeyVector[0];
		string primaryKeyAttributeID = entitysPrimaryKeyVector[1];

		vector<string> primaryKeyAttributeIDVector;		
		primaryKeyAttributeIDVector = StringUtil::split(primaryKeyAttributeID,',');
		
		//set primary key
		Entity* entity = static_cast<Entity*>(erModel->getComponentByID(entityID));
		entity->setPrimaryKey(VectorUtil::convertVectorToSet<string>(primaryKeyAttributeIDVector));
	}
}

void LoadFileCommand::addAllComponentToERModel(){	
	ERModel* erModel = this->presentation->getERModel();
	
	int index = 0;
	//add all component in queue
	while(!this->componentDataQueue.empty()){
		StringPair componentData = this->componentDataQueue.front();
		if(isQueueArriveConnectionDataID(index)){
			ConnectionData connectionData = this->connectionDataQueue.front();
			this->addConnector(connectionData,componentData.second);
		}
		else{
			Component* component = erModel->addNode(componentData.first);
			component->setName(componentData.second);
		}
		this->componentDataQueue.pop();		
		index++;
	}
}
//convert connectionData & add connector to ERModel
void LoadFileCommand::addConnector(ConnectionData connectionData,string connectionName){
	ERModel* erModel = this->presentation->getERModel();

	Component* firstNode = erModel->getComponentByID(connectionData.getConnectedFirstNodeID());
	Component* secondNode = erModel->getComponentByID(connectionData.getConnectedSecondNodeID());
	
	erModel->addConnection(firstNode,secondNode);
	Component* connector = erModel->getComponentByID(connectionData.getConnectorID());
	connector->setName(connectionName);
	this->connectionDataQueue.pop();
}
/*
*compare ComponentDataQueue & ConnectionDataQueue
*if ComponentDataQueue.front's ID equals ConnectionDataQueue.front's ID:
*	return true;//means to add connector
*/
bool LoadFileCommand::isQueueArriveConnectionDataID(int index){
	if(this->componentDataQueue.empty())
		return false;
	if(this->connectionDataQueue.empty())
		return false;
	if(StringUtil::intToString(index) == this->connectionDataQueue.front().getConnectorID())
		return true;

	return false;
}