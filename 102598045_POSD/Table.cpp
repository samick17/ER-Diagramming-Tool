#include "Table.h"
#include "ComponentUtil.h"

Table::Table(Entity* entity) : entity(entity){
}

Table::~Table(){
}
//all entity attribute (pk and attributes)
void Table::insertAllAttributes(set<Attribute*> attributeSet){
	this->attributeSet.insert(attributeSet.begin(),attributeSet.end());	
}
//all foreign key attribute
void Table::insertAllForeignKeyAttributes(set<Attribute*> attributeSet){
	this->foreignKeyAttributeSet.insert(attributeSet.begin(),attributeSet.end());
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
		if(attribute->isAttributeType(AttributeType::PrimaryKey))
			nameSet.insert(attribute->getName());
	}
	return nameSet;
}

set<string> Table::getAllDefaultKeyAttributesNameSet(){
	set<string> nameSet;
	for each(Attribute* attribute in this->attributeSet){
		if(attribute->isAttributeType(AttributeType::Default))
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