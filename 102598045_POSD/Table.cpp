#include "Table.h"
#include "ComponentUtil.h"

Table::Table(Entity* entity) : entity(entity){
}

Table::~Table(){
}
//all entity attribute (pk and attributes)
void Table::insertAllAttributes(HashMap<string,Attribute*> attributeSet){
	for each(Attribute* attribute in attributeSet){
		this->attributeSet.put(attribute->getID(),attribute);	
	}	
}
//all foreign key attribute
void Table::insertAllForeignKeyAttributes(HashMap<string,Attribute*> attributeSet){
	for each(Attribute* attribute in attributeSet){
		this->foreignKeyAttributeSet.put(attribute->getID(),attribute);	
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
	for each(Attribute* attribute in this->attributeSet){
		if(attribute->isPrimaryKey())
			nameSet.insert(attribute->getName());
	}
	return nameSet;
}

set<string> Table::getAllDefaultKeyAttributesNameSet(){
	set<string> nameSet;
	for each(Attribute* attribute in this->attributeSet){
		if(!attribute->isPrimaryKey())
			nameSet.insert(attribute->getName());
	}
	return nameSet;
}

set<string> Table::getAllForeignKeyAttributesNameSet(){
	set<string> nameSet;
	for each(Attribute* attribute in this->foreignKeyAttributeSet)		
			nameSet.insert(attribute->getName());	
	return nameSet;
}