#include "Table.h"
#include "AttributeType.h"
#include "NullPointerException.h"

Table::Table(Entity* entity) : entity(entity){
}

Table::~Table(){
}
//all entity attribute (pk and attributes)
void Table::insertAllAttributes(HashMap<string,Attribute*> attributeMap){
    for each(Attribute* attribute in attributeMap){
        if(attribute->isPrimaryKey())
            this->primaryKeyAttributeMap.put(attribute->getID(),attribute);
        else
            this->defaultAttributeMap.put(attribute->getID(),attribute);
        this->allAttributeMap.put(attribute->getID(),attribute);
    }
}
//all foreign key attribute
void Table::insertAllForeignKeyAttributes(HashMap<string,Attribute*> foreignKeyAttributeMap){
    for each(Attribute* attribute in foreignKeyAttributeMap){
        this->foreignKeyAttributeMap.put(attribute->getID(),attribute);
        this->allAttributeMap.put(attribute->getID(),attribute);
    }
}

string Table::getEntityID(){
    return this->entity->getID();
}

string Table::getEntityName(){
    return this->entity->getName();
}

HashMap<string,Attribute*> Table::getAllAttributeMap(){
    return this->allAttributeMap;
}

int Table::getAttributeType(Attribute* attribute){
    if(primaryKeyAttributeMap.containsKey(attribute->getID()))
        return AttributeType::PrimaryKey;
    else if(defaultAttributeMap.containsKey(attribute->getID()))
        return AttributeType::Default;
    else if(foreignKeyAttributeMap.containsKey(attribute->getID()))
        return AttributeType::ForeignKey;
    throw NullPointerException();
}

vector<string> Table::getAllPrimaryKeyAttributesNameVector(){
    vector<string> nameVector;
    for each(Attribute* attribute in this->primaryKeyAttributeMap)
            nameVector.push_back(attribute->getName());
    return nameVector;
}

vector<string> Table::getAllDefaultKeyAttributesNameVector(){
    vector<string> nameVector;
    for each(Attribute* attribute in this->defaultAttributeMap)
            nameVector.push_back(attribute->getName());
    return nameVector;
}

vector<string> Table::getAllForeignKeyAttributesNameVector(){
    vector<string> nameVector;
    for each(Attribute* attribute in this->foreignKeyAttributeMap)
            nameVector.push_back(attribute->getName());
    return nameVector;
}