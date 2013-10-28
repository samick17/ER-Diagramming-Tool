#include "Node.h"
#include "ERModel.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

Node::Node(ComponentData componentData) : Component(componentData){
}

Node::~Node(){
}

string Node::getType(){
    return ComponentType::TypeNode;
}
//break all connection in this all connectors
void Node::breakAllConnections(){
    for each(Component* connector in this->getAllConnections())    
        connector->breakAllConnections();
}

bool Node::hasSizeToConnect(){
    return true;
}
//@return NodeConnectionType's value
int Node::canConnectTo(Component* target){
    bool sameType = this->getType() == target->getType();    
    bool hasConnectedToTarget = this->hasConnectedTo(target);
    bool hasSizeToConnect = this->hasSizeToConnect() & target->hasSizeToConnect();
    
    //connect to self throw
    if(this == target)        
        throw ConnectedSelfException(this->getID());    
    //has already connected to target throw
    else if(hasConnectedToTarget)
        throw HasConnectedException(this->getID(),target->getID());
    //invalid connect: same type or is full
    else if(sameType || !hasSizeToConnect)
        throw InvalidConnectException(this->getID(),target->getID());

    return NodeConnectionType::ValidConnect;
}