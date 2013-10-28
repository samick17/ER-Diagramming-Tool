#include "ConnectNodeCommand.h"
#include "ERModel.h"
#include "StringUtil.h"
#include "ComponentUtil.h"
#include "Exception.h"
#include "NullPointerException.h"

using namespace std;

ConnectNodeCommand::ConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector) : erModel(erModel),firstNode(firstNode),secondNode(secondNode),connector(connector){
}

ConnectNodeCommand::~ConnectNodeCommand(){
    if(!this->executionFlag){
        delete this->connector;
    }
}

void ConnectNodeCommand::execute(){
	this->erModel->insertComponent(connector);
	ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
    this->executionFlag = true;
}

void ConnectNodeCommand::unExecute(){
    //disconnect node && remove connector from ERModel
    ComponentUtil::disconnectWithEachOther(this->firstNode,this->secondNode,this->connector);
    this->erModel->eraseComponent(this->connector);
    this->executionFlag = false;
}