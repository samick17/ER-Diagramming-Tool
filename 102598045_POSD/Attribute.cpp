#include "Attribute.h"
#include "ERModel.h"
#include "RelationShip.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentConnectionSize.h"

Attribute::Attribute(ComponentData componentData) : Node(componentData){
	this->attributeType = AttributeType::Default;
}

Attribute::~Attribute(){
}

string Attribute::getType(){
	return ComponentType::TypeAttribute;
}

int Attribute::canConnectTo(Component* target){
	int canConnect = Node::canConnectTo(target);

	if(typeid(*target).name() == typeid(RelationShip).name())
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
	this->attributeType = AttributeType::PrimaryKey;
}

Component* Attribute::clone() const{ 
	return new Attribute(*this); 
}