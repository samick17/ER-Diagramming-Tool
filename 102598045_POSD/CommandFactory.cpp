#include "CommandFactory.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "ERModel.h"
#include "Node.h"
#include "Connector.h"

Command* CommandFactory::createAddNodeCommand(ERModel* erModel,Node* node){
    return new AddNodeCommand(erModel,node);
}

Command* CommandFactory::createConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector){
    return new ConnectNodeCommand(erModel,firstNode,secondNode,connector);
}

Command* CommandFactory::createDeleteComponentCommand(ERModel* erModel,Component* component){
    return new DeleteComponentCommand(erModel,component);
}