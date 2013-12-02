#include "ConnectNodeCommand.h"
#include "ERModel.h"
#include "ComponentUtil.h"

using namespace std;

ConnectNodeCommand::ConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector) : erModel(erModel),firstNode(firstNode),secondNode(secondNode),connector(connector){
}

ConnectNodeCommand::~ConnectNodeCommand(){
    if(!this->getExecutionFalg())
        delete this->connector;
}

void ConnectNodeCommand::doExecute(){
    this->erModel->insertComponent(connector);
    ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
}

void ConnectNodeCommand::doUnExecute(){
    //disconnect node && remove connector from ERModel
    ComponentUtil::disconnectWithEachOther(this->firstNode,this->secondNode,this->connector);
    this->erModel->eraseComponent(this->connector);
}