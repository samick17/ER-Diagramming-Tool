#include "Connector.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentUtil.h"
#include "ComponentConnectionSize.h"
#include "ConnectorData.h"
#include "Number.h"

Connector::Connector(string componentID,string componentName){
    this->componentData = new ConnectorData(componentID,componentName);
}

Connector::~Connector(){
}

//connector cannot set position freely
void Connector::setPosition(Point position){
}
//connector cannot set position freely
void Connector::setCenterPosition(Point position){
}

void Connector::updateRect(){
    Component* firstNode = this->getFirstConnectedNode();
    Component* secondNode = this->getSecondConnectedNode();
    if(!firstNode && !secondNode)
        return;
    Rect sourceRect = firstNode->getRect();
    Rect targetRect = secondNode->getRect();
    pair<Point,Point> minDistancePointPair = sourceRect.getMinDistanceToRectPoint(targetRect);

    ConnectorData* connectorData = static_cast<ConnectorData*>(this->componentData);
    connectorData->setPointPair(minDistancePointPair);
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

bool Connector::isCardinalityConnector(){
    int attributeCount = 0,entityCount = 0,relationShipCount = 0;
    HashMap<string,int*> countingMap;
    countingMap.put(ComponentType::TypeAttribute,&attributeCount);
    countingMap.put(ComponentType::TypeEntity,&entityCount);
    countingMap.put(ComponentType::TypeRelationShip,&relationShipCount);
    for each(Component* connection in this->getAllConnections())
        (*countingMap.get(connection->getType()))++;
    if(entityCount == Number::One && relationShipCount == Number::One)
        return true;
    return false;
}

Component* Connector::clone() const{
    return new Connector(*this);
}