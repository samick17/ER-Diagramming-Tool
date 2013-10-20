#include "Entity.h"
#include "ERModel.h"
#include "Attribute.h"
#include "RelationShip.h"
#include "ComponentUtil.h"
#include "ComponentType.h"
#include "StringUtil.h"
#include "NoConnectionException.h"
#include "EmptyCollectionException.h"

Entity::Entity(ComponentData componentData) : Node(componentData){
}

Entity::~Entity(){
}
//format: entityID pkID1,pkID2,....pkIDn
string Entity::toString(){	
	HashMap<string,Attribute*> primaryKeyAttributeHashMap = this->getPrimaryKeyAttributes();

	if(primaryKeyAttributeHashMap.empty())
		return "";

	string result = this->getID();
	set<string> primaryKeyAttributeIDSet;

	for each(Attribute* attribute in primaryKeyAttributeHashMap)	
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

HashMap<string,Attribute*> Entity::getConnectedAttributes(){
	HashMap<string,Attribute*> connectedAttributeMap = ComponentUtil::getConnectedNodeHashMapByType<Attribute>(this->getAllConnections());

	if(connectedAttributeMap.empty()){		
		throw EmptyCollectionException(ComponentType::TypeAttributeName);
	}

	return connectedAttributeMap;
}
//get Attribute By ID, if doesn't has such attribute, throw exception
Attribute* Entity::getAttributeByID(string id){
	HashMap<string,Attribute*> attributeMap = this->getConnectedAttributes();

	for each(Attribute* attribute in attributeMap){
		if(attribute->getID() == id)		
			return attribute;		
	}

	throw NoConnectionException(id,this->getID());
}

HashMap<string,Attribute*> Entity::getPrimaryKeyAttributes(){
	HashMap<string,Attribute*> attributeMap;
	for each(Attribute* attribute in this->getConnectedAttributes()){
		if(attribute->isPrimaryKey())
			attributeMap.put(attribute->getID(),attribute);
	}
	return attributeMap;
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