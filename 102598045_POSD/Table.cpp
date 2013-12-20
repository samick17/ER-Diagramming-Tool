#include "Table.h"
#include "AttributeType.h"
#include "NullPointerException.h"
#include "StringUtil.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"

Table::Table(Entity* entity) : node(entity){
}

Table::Table(RelationShip* relationShip) : node(relationShip){
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

string Table::getTableID(){
    return this->node->getID();
}

string Table::getTableName(){
    return this->node->getName();
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

string Table::toString(){
    vector<string> stringVector;
    stringVector.push_back(this->appendAttributeToString(this->primaryKeyAttributeMap," PK(",")"));
    stringVector.push_back(this->appendAttributeToString(this->defaultAttributeMap));
    stringVector.push_back(this->appendAttributeToString(this->foreignKeyAttributeMap," FK(",")"));
    return StringUtil::appendWithComma(stringVector);
}

string Table::appendAttributeToString(HashMap<string,Attribute*> attributeMap,string startString,string endString){
    if(attributeMap.empty())
        return StringSymbol::Empty;
    string result = startString;
    vector<string> attributeNameVector;
    for each(Attribute* attribute in attributeMap)
        attributeNameVector.push_back(attribute->getName());
    result+= StringUtil::appendWithComma(attributeNameVector);
    result += endString;
    return result;
}