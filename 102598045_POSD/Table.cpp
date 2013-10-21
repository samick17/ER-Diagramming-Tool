#include "Table.h"
#include "ComponentUtil.h"

Table::Table(Entity* entity) : entity(entity){
}

Table::~Table(){
}
//all entity attribute (pk and attributes)
void Table::insertAllAttributes(HashMap<string,Attribute*> attributeMap){
	for each(Attribute* attribute in attributeMap){
		this->attributeMap.put(attribute->getID(),attribute);	
	}	
}
//all foreign key attribute
void Table::insertAllForeignKeyAttributes(HashMap<string,Attribute*> foreignKeyAttributeMap){
	for each(Attribute* attribute in attributeMap){
		this->foreignKeyAttributeMap.put(attribute->getID(),attribute);	
	}	
}

string Table::getEntityID(){
	return this->entity->getID();
}

string Table::getEntityName(){
	return this->entity->getName();
}

set<string> Table::getAllPrimaryKeyAttributesNameSet(){
	set<string> nameSet;
	for each(Attribute* attribute in this->attributeMap){
		if(attribute->isPrimaryKey())
			nameSet.insert(attribute->getName());
	}
	return nameSet;
}

set<string> Table::getAllDefaultKeyAttributesNameSet(){
	set<string> nameSet;
	for each(Attribute* attribute in this->attributeMap){
		if(!attribute->isPrimaryKey())
			nameSet.insert(attribute->getName());
	}
	return nameSet;
}

set<string> Table::getAllForeignKeyAttributesNameSet(){
	set<string> nameSet;
	for each(Attribute* attribute in this->foreignKeyAttributeMap)		
			nameSet.insert(attribute->getName());	
	return nameSet;
}