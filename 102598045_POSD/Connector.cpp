#include "Connector.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentUtil.h"
#include "ComponentConnectionSize.h"
#include "StringSymbol.h"

Connector::Connector(ComponentData componentData) : Component(componentData){
}

Connector::~Connector(){
}

string Connector::getType(){
    return ComponentType::TypeConnector;
}

void Connector::setPosition(Point position){
}

void Connector::setCenterPosition(Point position){
}

void Connector::updateRect(){
    Component* firstNode = this->getFirstConnectedNode();
    Component* secondNode = this->getSecondConnectedNode();
    if(!firstNode && !secondNode)
        return;
    Point sourcePoint = firstNode->getRect().getCenterPosition();
    Point targetPoint = secondNode->getRect().getCenterPosition();

    Point position = Point(min(sourcePoint.getX(),targetPoint.getX()),min(sourcePoint.getY(),targetPoint.getY()));
    this->componentData.setPosition(position);
    Size size = Size(abs(sourcePoint.getX()-targetPoint.getX()),abs(sourcePoint.getY()-targetPoint.getY()));
    this->componentData.setSize(size);
}

void Connector::breakAllConnections(){
    Component* firstNode = this->getFirstConnectedNode();
    Component* secondNode = this->getSecondConnectedNode();

    ComponentUtil::disconnectWithEachOther(firstNode,secondNode,this);
}

int Connector::canConnectTo(Component* target){
    throw InvalidConnectException(this->getID(),target->getID());
}

bool Connector::hasSizeToConnect(){
    return this->getAllConnections().size() < ComponentConnectionSize::ConnectorConnectionSize;
}
//first node's id will always less than second node
Component* Connector::getFirstConnectedNode(){
    HashMap<string,Component*> connectionMap = this->getAllConnections();
    if(connectionMap.empty())
        return NULL;
    return connectionMap.getValueByIndex(0);
}
//second node's id will always greater than first node
Component* Connector::getSecondConnectedNode(){
    HashMap<string,Component*> connectionMap = this->getAllConnections();
    if(connectionMap.size()>1)
        return connectionMap.getValueByIndex(1);
    return NULL;
}

bool Connector::isNodesConnection(Component* firstNode,Component* secondNode){
    if(firstNode == secondNode)
        return false;

    bool isConnection = false;
    HashMap<string,Component*> connections = this->getAllConnections();

    isConnection = connections.containsKey(firstNode->getID());
    isConnection &= connections.containsKey(secondNode->getID());

    return isConnection;
}