#include "SaveXmlComponentVisitor.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringSymbol.h"
#include "StringUtil.h"

SaveXmlComponentVisitor::SaveXmlComponentVisitor(HashMap<string,string> reorderedIDMap) : ComponentVisitor(reorderedIDMap){
}

SaveXmlComponentVisitor::~SaveXmlComponentVisitor(){
}

const vector<string> SaveXmlComponentVisitor::getResult(){
    return this->componentInfoVector;
}

void SaveXmlComponentVisitor::visit(Attribute* attribute){
    this->componentInfoVector.push_back(StringSymbol::Tab+"<Attribute>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Id>"+attribute->getID()+"</Id>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Text>"+attribute->getName()+"</Text>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PositionX>"+StringUtil::intToString(attribute->getRect().getPosition().getX())+"</PositionX>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PositionY>"+StringUtil::intToString(attribute->getRect().getPosition().getY())+"</PositionY>");
    this->componentInfoVector.push_back(StringSymbol::Tab+"</Attribute>");
}

void SaveXmlComponentVisitor::visit(Entity* entity){
    this->componentInfoVector.push_back(StringSymbol::Tab+"<Entity>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Id>"+entity->getID()+"</Id>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Text>"+entity->getName()+"</Text>");
    for each(Attribute* attribute in entity->getPrimaryKeyAttributes())
        this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PrimaryKey>"+attribute->getID()+"</PrimaryKey>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PositionX>"+StringUtil::intToString(entity->getRect().getPosition().getX())+"</PositionX>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PositionY>"+StringUtil::intToString(entity->getRect().getPosition().getY())+"</PositionY>");
    this->componentInfoVector.push_back(StringSymbol::Tab+"</Entity>");
}


void SaveXmlComponentVisitor::visit(RelationShip* relationShip){
    this->componentInfoVector.push_back(StringSymbol::Tab+"<RelationShip>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Id>"+relationShip->getID()+"</Id>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Text>"+relationShip->getName()+"</Text>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PositionX>"+StringUtil::intToString(relationShip->getRect().getPosition().getX())+"</PositionX>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<PositionY>"+StringUtil::intToString(relationShip->getRect().getPosition().getY())+"</PositionY>");
    this->componentInfoVector.push_back(StringSymbol::Tab+"</RelationShip>");
}

void SaveXmlComponentVisitor::visit(Connector* connector){
    this->componentInfoVector.push_back(StringSymbol::Tab+"<Connector>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Id>"+connector->getID()+"</Id>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Text>"+connector->getName()+"</Text>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Source>"+connector->getFirstConnectedNode()->getID()+"</Source>");
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+"<Target>"+connector->getSecondConnectedNode()->getID()+"</Target>");
    this->componentInfoVector.push_back(StringSymbol::Tab+"</Connector>");
}