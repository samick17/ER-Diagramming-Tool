#include "Attribute.h"
#include "RelationShip.h"
#include "ComponentType.h"
#include "AttributeType.h"
#include "InvalidConnectException.h"
#include "ComponentConnectionSize.h"
#include "ComponentVisitor.h"

Attribute::Attribute(string componentID,string componentName) : Node(ComponentType::TypeAttribute,componentID,componentName){
    this->attributeType = AttributeType::Default;
}

Attribute::~Attribute(){
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

void Attribute::accept(ComponentVisitor* visitor){
    visitor->visit(this);
}

Component* Attribute::clone() const{
    Attribute* attribute = new Attribute("",this->componentData->getName());
    Point newPosition = Point(this->componentData->getRect().getPosition().getX()+20,this->componentData->getRect().getPosition().getY()+20);
    attribute->setPosition(newPosition);
    return attribute;
}