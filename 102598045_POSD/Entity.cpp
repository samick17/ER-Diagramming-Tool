#include "Entity.h"
#include "ERModel.h"
#include "Attribute.h"
#include "RelationShip.h"
#include "ComponentUtil.h"
#include "ComponentType.h"
#include "StringUtil.h"
#include "NoConnectionException.h"

Entity::Entity(ComponentData componentData) : Node(componentData){
}

Entity::~Entity(){
}
//format: entityID pkID1,pkID2,....pkIDn
string Entity::toString(){	
	set<Attribute*> primaryKeyAttributeSet = this->getPrimaryKeyAttributes();

	if(primaryKeyAttributeSet.empty())
		return "";

	string result = this->getID();
	set<string> primaryKeyAttributeIDSet;

	for each(Attribute* attribute in primaryKeyAttributeSet)	
		primaryKeyAttributeIDSet.insert(attribute->getID());	

	result += " "+StringUtil::appendWithComma(primaryKeyAttributeIDSet);

	return result;
}

string Entity::getType(){
	return ComponentType::TypeEntity;
}

int Entity::canConnectTo(Component* target){	
	int canConnect = Node::canConnectTo(target);	
	
	if(typeid(*target).name() == typeid(RelationShip).name())		
		canConnect = NodeConnectionType::ConnectEntityAndRelation;		
	
	return canConnect;
}

bool Entity::hasSizeToConnect(){
	return true;
}

set<Attribute*> Entity::getConnectedAttributes(){
	return ComponentUtil::getConnectedNodeSetByType<Attribute>(this->getAllConnectors());
}
//get Attribute By ID, if doesn't has such attribute, throw exception
Attribute* Entity::getAttributeByID(string id){
	set<Attribute*> attributeSet = this->getConnectedAttributes();

	for each(Attribute* attribute in attributeSet){
		if(attribute->getID() == id)		
			return attribute;		
	}

	throw NoConnectionException(id,this->getID());
}

set<Attribute*> Entity::getPrimaryKeyAttributes(){
	set<Attribute*> attributeSet;
	for each(Attribute* attribute in this->getConnectedAttributes()){
		if(attribute->isPrimaryKey())
			attributeSet.insert(attribute);
	}
	return attributeSet;
}
//set this primary key by primary key collection, if doesn't has such attribute, throw exception
void Entity::setPrimaryKey(set<string> primaryKeyIDSet){
	for each (string attributeID in primaryKeyIDSet){
		Attribute* attribute = this->getAttributeByID(attributeID);			
		attribute->setAsPrimaryKey();		
	}
}

Component* Entity::clone() const
{ 
	return new Entity(*this); 
}