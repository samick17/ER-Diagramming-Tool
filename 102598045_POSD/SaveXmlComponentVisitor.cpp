#include "SaveXmlComponentVisitor.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringSymbol.h"
#include "StringUtil.h"

const string SaveXmlComponentVisitor::XmlStart = "<?xml version=\"1.0\"?>";
const string SaveXmlComponentVisitor::ERDiagramStart = "<ERDiagram>",SaveXmlComponentVisitor::ERDiagramEnd = "</ERDiagram>";
const string SaveXmlComponentVisitor::AttributeStart = "<Attribute>",SaveXmlComponentVisitor::AttributeEnd = "</Attribute>";
const string SaveXmlComponentVisitor::EntityStart = "<Entity>",SaveXmlComponentVisitor::EntityEnd = "</Entity>";
const string SaveXmlComponentVisitor::RelationShipStart = "<RelationShip>",SaveXmlComponentVisitor::RelationShipEnd = "</RelationShip>";
const string SaveXmlComponentVisitor::ConnectorStart = "<Connector>",SaveXmlComponentVisitor::ConnectorEnd = "</Connector>";
const string SaveXmlComponentVisitor::IdStart = "<Id>",SaveXmlComponentVisitor::IdEnd = "</Id>";
const string SaveXmlComponentVisitor::TextStart = "<Text>",SaveXmlComponentVisitor::TextEnd = "</Text>";
const string SaveXmlComponentVisitor::PositionXStart = "<PositionX>",SaveXmlComponentVisitor::PositionXEnd = "</PositionX>";
const string SaveXmlComponentVisitor::PositionYStart = "<PositionY>",SaveXmlComponentVisitor::PositionYEnd = "</PositionY>";
const string SaveXmlComponentVisitor::PrimaryKeyStart = "<PrimaryKey>",SaveXmlComponentVisitor::PrimaryKeyEnd = "</PrimaryKey>";
const string SaveXmlComponentVisitor::SourceStart = "<Source>",SaveXmlComponentVisitor::SourceEnd = "</Source>";
const string SaveXmlComponentVisitor::TargetStart = "<Target>",SaveXmlComponentVisitor::TargetEnd = "</Target>";

SaveXmlComponentVisitor::SaveXmlComponentVisitor(HashMap<string,string> reorderedIDMap) : ComponentVisitor(reorderedIDMap){
}

SaveXmlComponentVisitor::~SaveXmlComponentVisitor(){
}

const vector<string> SaveXmlComponentVisitor::getResult(){
    vector<string> result;
    result.push_back(XmlStart);
    result.push_back(ERDiagramStart);
    for each(string componentInfo in this->componentInfoVector)
        result.push_back(componentInfo);
    result.push_back(ERDiagramEnd);
    return result;
}

void SaveXmlComponentVisitor::visit(Attribute* attribute){
    this->componentInfoVector.push_back(StringSymbol::Tab+AttributeStart);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+IdStart+this->getTransformedID(attribute)+IdEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+TextStart+attribute->getName()+TextEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PositionXStart+StringUtil::doubleToString(attribute->getRect().getPosition().getX())+PositionXEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PositionYStart+StringUtil::doubleToString(attribute->getRect().getPosition().getY())+PositionYEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+AttributeEnd);
}

void SaveXmlComponentVisitor::visit(Entity* entity){
    this->componentInfoVector.push_back(StringSymbol::Tab+EntityStart);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+IdStart+this->getTransformedID(entity)+IdEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+TextStart+entity->getName()+TextEnd);
    for each(Attribute* attribute in entity->getPrimaryKeyAttributes())
        this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PrimaryKeyStart+this->getTransformedID(attribute)+PrimaryKeyEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PositionXStart+StringUtil::doubleToString(entity->getRect().getPosition().getX())+PositionXEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PositionYStart+StringUtil::doubleToString(entity->getRect().getPosition().getY())+PositionYEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+EntityEnd);
}

void SaveXmlComponentVisitor::visit(RelationShip* relationShip){
    this->componentInfoVector.push_back(StringSymbol::Tab+RelationShipStart);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+IdStart+this->getTransformedID(relationShip)+IdEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+TextStart+relationShip->getName()+TextEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PositionXStart+StringUtil::doubleToString(relationShip->getRect().getPosition().getX())+PositionXEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+PositionYStart+StringUtil::doubleToString(relationShip->getRect().getPosition().getY())+PositionYEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+RelationShipEnd);
}

void SaveXmlComponentVisitor::visit(Connector* connector){
    this->componentInfoVector.push_back(StringSymbol::Tab+ConnectorStart);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+IdStart+this->getTransformedID(connector)+IdEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+TextStart+connector->getName()+TextEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+SourceStart+this->getTransformedID(connector->getFirstConnectedNode())+SourceEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+StringSymbol::Tab+TargetStart+this->getTransformedID(connector->getSecondConnectedNode())+TargetEnd);
    this->componentInfoVector.push_back(StringSymbol::Tab+ConnectorEnd);
}