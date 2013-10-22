#include "FileParser.h"
#include "StringUtil.h"
#include "VectorUtil.h"
#include "StringSymbol.h"
#include "CharSymbol.h"

FileParser::FileParser(){
	this->erModel = NULL;
}

FileParser::~FileParser(){
}

void FileParser::parseFileToModel(string filePath,ERModel* erModel){
	//load all file
	Document doc(filePath);
	doc.openFile();

	this->erModel = erModel;

	this->erModel->clearComponentMap();

	//load all Nodes & Connectors
	this->loadAllComponentsFromDoc(doc);
	this->loadAllConnectorsFromDoc(doc);
	this->addAllComponentToERModel();
	//load all Primary Key
	this->loadAllPrimaryKeyAndSetUpFromDoc(doc);
}

void FileParser::loadAllComponentsFromDoc(Document& doc){	
	string line;
	while((line = doc.readLine()) != StringSymbol::Empty){
		//load component data & push to componentDataQueue
		vector<string> componentDataVector = StringUtil::split(line,CharSymbol::Comma);
		string type = StringUtil::trim(componentDataVector[0]);
		string name = StringSymbol::Empty;

		//load component name
		if(componentDataVector.size() > 1)		
			name = StringUtil::trim(componentDataVector[1]);

		this->componentDataQueue.push(StringPair(type,name));		
	}
}

void FileParser::loadAllConnectorsFromDoc(Document& doc){
	string line;
	while((line = doc.readLine()) != StringSymbol::Empty){
		//load connection data & push to connectionDataQueue
		vector<string> connectorDataVector = StringUtil::split(line,CharSymbol::Space);
		vector<string> connectorNodeIDVector = StringUtil::split(connectorDataVector[1],CharSymbol::Comma);

		string connectorID = StringUtil::trim(connectorDataVector[0]);
		string firstNodeID = StringUtil::trim(connectorNodeIDVector[0]);
		string secondNodeID = StringUtil::trim(connectorNodeIDVector[1]);

		ConnectionData connectionData(connectorID,firstNodeID,secondNodeID);

		this->connectionDataQueue.push(connectionData);
	}
}

void FileParser::loadAllPrimaryKeyAndSetUpFromDoc(Document& doc){
	string line;
	while((line = doc.readLine()) != StringSymbol::Empty){
		vector<string> entitysPrimaryKeyVector = StringUtil::split(line,CharSymbol::Space);
		string entityID = entitysPrimaryKeyVector[0];
		string primaryKeyAttributeID = entitysPrimaryKeyVector[1];

		vector<string> primaryKeyAttributeIDVector;		
		primaryKeyAttributeIDVector = StringUtil::split(primaryKeyAttributeID,CharSymbol::Comma);
		
		//set primary key
		Entity* entity = static_cast<Entity*>(this->erModel->getComponentByID(entityID));
		entity->setPrimaryKey(VectorUtil::convertVectorToSet<string>(primaryKeyAttributeIDVector));
	}
}

void FileParser::addAllComponentToERModel(){	
	int index = 0;
	//add all component in queue
	while(!this->componentDataQueue.empty()){
		StringPair componentData = this->componentDataQueue.front();
		if(isQueueArriveConnectionDataID(index)){
			ConnectionData connectionData = this->connectionDataQueue.front();
			this->addConnector(connectionData,componentData.second);
		}
		else {
			Component* component = this->erModel->addNode(componentData.first);
			component->setName(componentData.second);
		}
		this->componentDataQueue.pop();		
		index++;
	}
}
//convert connectionData & add connector to ERModel
void FileParser::addConnector(ConnectionData connectionData,string connectionName){
	Component* firstNode = this->erModel->getComponentByID(connectionData.getConnectedFirstNodeID());
	Component* secondNode = erModel->getComponentByID(connectionData.getConnectedSecondNodeID());
	
	this->erModel->addConnection(firstNode,secondNode);
	Component* connector = this->erModel->getComponentByID(connectionData.getConnectorID());
	connector->setName(connectionName);
	this->connectionDataQueue.pop();
}
/*
*compare ComponentDataQueue & ConnectionDataQueue
*if ComponentDataQueue.front's ID equals ConnectionDataQueue.front's ID:
*	return true;//means to add connector
*/
bool FileParser::isQueueArriveConnectionDataID(int index){
	if(this->componentDataQueue.empty())
		return false;
	if(this->connectionDataQueue.empty())
		return false;
	if(StringUtil::intToString(index) == this->connectionDataQueue.front().getConnectorID())
		return true;

	return false;
}