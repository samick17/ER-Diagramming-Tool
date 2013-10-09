#include "ConnectNodeCommand.h"
#include "ERModel.h"
#include "StringUtil.h"
#include "ConnectionReceiverManager.h"
#include "FindComponentCommand.h"
#include "ComponentUtil.h"

using namespace std;

ConnectNodeCommand :: ConnectNodeCommand(Presentation* presentation) : UnexecutableCommand(presentation){	
	this->connector = NULL;
}

ConnectNodeCommand::~ConnectNodeCommand(){
	if(!this->getExecutionFlag())
		delete this->connector;
}

void ConnectNodeCommand :: execute(){	
	if(this->connector != NULL){
		//connect two node, and add connector to ERModel
		ComponentUtil::connectWithEachOther(this->firstNode,this->secondNode,this->connector);

		ERModel* erModel = this->presentation->getERModel();
		erModel->addComponent(this->connector);
	}
	else 	
		this->doConnectTwoNode();
	
	this->UnexecutableCommand::execute();
}

void ConnectNodeCommand::unExecute(){
	//disconnect node && remove connector from ERModel
	ComponentUtil::disconnectWithEachOther(this->firstNode,this->secondNode,this->connector);

	ERModel* erModel = this->presentation->getERModel();
	erModel->removeComponentByID(this->connector->getID());

	this->UnexecutableCommand::unExecute();
}

void ConnectNodeCommand::doConnectTwoNode(){	
	ERModel* erModel = this->presentation->getERModel();
		
	FindComponentCommand findComponentCommand(this->presentation);
	//Find First Node
	findComponentCommand.setInfo("Please enter the first node ID");
	findComponentCommand.execute();	
	Component* firstNode = findComponentCommand.getComponent();

	//Find Second Node
	findComponentCommand.setInfo("Please enter the second node ID");
	findComponentCommand.execute();
	Component* secondNode = findComponentCommand.getComponent();

	int nodeConnectionType = erModel->addConnection(firstNode,secondNode);

	this->backupConnectInfo(firstNode,secondNode);

	ConnectionReceiverManager connectionReceiverManager(this->presentation,firstNode,secondNode);
	connectionReceiverManager.response(nodeConnectionType);
}
//backup firstNode,secondNode,and its connector
void ConnectNodeCommand::backupConnectInfo(Component* firstNode,Component* secondNode){
	this->firstNode = firstNode;
	this->secondNode = secondNode;

	ERModel* erModel = this->presentation->getERModel();	
	Component* connector = erModel->getNodesConnector(firstNode,secondNode);	
	this->connector = connector;
}