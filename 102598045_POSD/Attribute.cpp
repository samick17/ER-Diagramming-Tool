#include "Attribute.h"
#include "RelationShip.h"
#include "ComponentType.h"
#include "AttributeType.h"
#include "InvalidConnectException.h"
#include "ComponentConnectionSize.h"

Attribute::Attribute(string componentID,string componentName) : Node(ComponentType::TypeAttribute,componentID,componentName){
    this->attributeType = AttributeType::Default;
}

Attribute::~Attribute(){
}

void Attribute::postDisconnect(){
    this->setAsDefaultKey();
}

int Attribute::canConnectTo(Component* target){
    int canConnect = Node::canConnectTo(target);

    if(target->isTypeOf<RelationShip>())
        throw InvalidConnectException(this->getID(),target->getID());

    return canConnect;
}

bool Attribute::hasSizeToConnect(){
    return this->getAllConnections().size() < ComponentConnectionSize::AttributeConnectionSize;
}

bool Attribute::isPrimaryKey(){
    return this->attributeType == AttributeType::PrimaryKey;
}
//set attribute as general
void Attribute::setAsPrimaryKey(){
    this->componentData->setIsUnderLine(true);
    this->attributeType = AttributeType::PrimaryKey;
}

void Attribute::setAsDefaultKey(){
    this->componentData->setIsUnderLine(false);
    this->attributeType = AttributeType::Default;
}