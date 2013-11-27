#include "Table.h"

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
    for each(Attribute* attribute in foreignKeyAttributeMap){
        this->foreignKeyAttributeMap.put(attribute->getID(),attribute);
    }    
}

string Table::getEntityID(){
    return this->entity->getID();
}

string Table::getEntityName(){
    return this->entity->getName();
}

vector<string> Table::getAllPrimaryKeyAttributesNameVector(){
    vector<string> nameVector;
    for each(Attribute* attribute in this->attributeMap){
        if(attribute->isPrimaryKey())
            nameVector.push_back(attribute->getName());
    }
    return nameVector;
}

vector<string> Table::getAllDefaultKeyAttributesNameVector(){
    vector<string> nameVector;
    for each(Attribute* attribute in this->attributeMap){
        if(!attribute->isPrimaryKey())
            nameVector.push_back(attribute->getName());
    }
    return nameVector;
}

vector<string> Table::getAllForeignKeyAttributesNameVector(){
    vector<string> nameVector;
    for each(Attribute* attribute in this->foreignKeyAttributeMap)
            nameVector.push_back(attribute->getName());
    return nameVector;
}