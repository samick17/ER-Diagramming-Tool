#include "CommandFactory.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "SetPrimaryKeyCommand.h"
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

Command* CommandFactory::createSetPrimaryKeyCommand(ERModel* erModel,Attribute* attribute){
    return new SetPrimaryKeyCommand(erModel,attribute);
}