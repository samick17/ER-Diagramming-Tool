#include "Node.h"
#include "Connector.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

Node::Node(string type,string componentID,string componentName){
    this->componentData = new ComponentData(type,componentID,componentName);
}

Node::~Node(){
}

void Node::setPosition(Point position){
    this->componentData->setPosition(position);
    this->updateConnectorsPosition();
}

void Node::setCenterPosition(Point position){
    this->componentData->setCenterPosition(position);
    this->updateConnectorsPosition();
}

void Node::updateConnectorsPosition(){
    for each(Component* component in this->getAllConnections()){
        Connector* connector = static_cast<Connector*>(component);
        connector->updateRect();
    }
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