#include "ConnectNodeCommand.h"
#include "ERModel.h"
#include "ComponentUtil.h"

using namespace std;

ConnectNodeCommand::ConnectNodeCommand(HashMap<string,Component*>& componentMap,Component* firstNode,Component* secondNode,Connector* connector) : componentMap(componentMap),firstNode(firstNode),secondNode(secondNode),connector(connector){
}

ConnectNodeCommand::~ConnectNodeCommand(){
    if(!this->getExecutionFalg())
        delete this->connector;
}

void ConnectNodeCommand::doExecute(){
    this->componentMap.put(connector->getID(),connector);
    ComponentUtil::connectWithEachOther(firstNode,secondNode,connector);
}

void ConnectNodeCommand::doUnExecute(){
    //disconnect node && remove connector from ERModel
    ComponentUtil::disconnectWithEachOther(this->firstNode,this->secondNode,this->connector);
    this->componentMap.remove(this->connector->getID());
}