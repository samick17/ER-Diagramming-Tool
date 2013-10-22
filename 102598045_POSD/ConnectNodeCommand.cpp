#include "ConnectNodeCommand.h"
#include "ERModel.h"
#include "StringUtil.h"
#include "ConnectionReceiverManager.h"
#include "FindComponentCommand.h"
#include "ComponentUtil.h"
#include "Exception.h"
#include "NullPointerException.h"

using namespace std;

ConnectNodeCommand :: ConnectNodeCommand(Presentation* presentation) : UnexecutableCommand(presentation){	
	this->connector = NULL;
}

ConnectNodeCommand::~ConnectNodeCommand(){
	if(!this->getExecutionFlag()){
		delete this->connector;
	}
}
/**Non testable function**/
void ConnectNodeCommand::setupCommand(){
	FindComponentCommand findComponentCommand(this->presentation);
	//Find First Node
	findComponentCommand.setInfo("Please enter the first node ID");
	findComponentCommand.execute();	
	Component* firstNode = findComponentCommand.getComponent();

	//Find Second Node
	findComponentCommand.setInfo("Please enter the second node ID");
	findComponentCommand.execute();
	Component* secondNode = findComponentCommand.getComponent();

	ERModel* erModel = this->presentation->getERModel();	
	int nodeConnectionType = erModel->addConnection(firstNode,secondNode);
	//back up connector for undo this command
	this->backupConnector(firstNode,secondNode);
	//trigger response for connection result
	ConnectionReceiverManager connectionReceiverManager(this->presentation,firstNode,secondNode);
	connectionReceiverManager.response(nodeConnectionType);
}

void ConnectNodeCommand :: execute(){
	if(this->getExecutionFlag())
		return;		
	ERModel* erModel = this->presentation->getERModel();
	
	if(this->connector == NULL){
		erModel->addConnection(firstNode,secondNode);
		this->backupConnector(firstNode,secondNode);
	}else {
		try{
			erModel->getComponentByID(this->connector->getID());
		}
		catch(Exception&){
			ComponentUtil::connectWithEachOther(this->firstNode,this->secondNode,this->connector);
			erModel->insertComponent(this->connector);
		}
	}
	this->UnexecutableCommand::execute();
}

void ConnectNodeCommand::unExecute(){
	if(!this->getExecutionFlag())
		return;
	//disconnect node && remove connector from ERModel
	ComponentUtil::disconnectWithEachOther(this->firstNode,this->secondNode,this->connector);

	ERModel* erModel = this->presentation->getERModel();
	erModel->eraseComponent(this->connector);

	this->UnexecutableCommand::unExecute();
}
//backup firstNode,secondNode,and its connector
void ConnectNodeCommand::backupConnector(Component* firstNode,Component* secondNode){
	this->firstNode = firstNode;
	this->secondNode = secondNode;

	ERModel* erModel = this->presentation->getERModel();

	Component* connector = erModel->getNodesConnector(firstNode,secondNode);	
	this->connector = connector;
}