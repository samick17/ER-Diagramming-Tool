#include "SaveComponentVisitor.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringSymbol.h"
#include "Component.h"
#include "StringUtil.h"

SaveComponentVisitor::SaveComponentVisitor(){
}

SaveComponentVisitor::~SaveComponentVisitor(){
}

const vector<string> SaveComponentVisitor::getResult(){
    vector<string> result = this->componentInfoVector;
    result.push_back(StringSymbol::Empty);
    result.insert(result.end(),this->connectionInfoVector.begin(),this->connectionInfoVector.end());
    result.push_back(StringSymbol::Empty);
    result.insert(result.end(),this->primaryKeyInfoVector.begin(),this->primaryKeyInfoVector.end());
    return result;
}

void SaveComponentVisitor::doVisit(Attribute* attribute){
    this->visitComponent(attribute);
}

void SaveComponentVisitor::doVisit(Entity* entity){
    this->visitComponent(entity);
    if(entity->getPrimaryKeyAttributes().empty())
        return;
    string info;
    info.append(this->getTransformedID(entity));
    info.append(StringSymbol::Space);
    vector<string> primaryKeyAttributeIDs;
    for each(Attribute* attribute in entity->getPrimaryKeyAttributes())
        primaryKeyAttributeIDs.push_back(this->getTransformedID(attribute));
    info.append(StringUtil::appendWithComma(primaryKeyAttributeIDs));
    this->primaryKeyInfoVector.push_back(info);
}


void SaveComponentVisitor::doVisit(RelationShip* relationShip){
    this->visitComponent(relationShip);
}

void SaveComponentVisitor::doVisit(Connector* connector){
    this->visitComponent(connector);
    string info;
    info.append(this->getTransformedID(connector));
    info.append(StringSymbol::Space);
    info.append(this->getTransformedID(connector->getFirstConnectedNode()));
    info.append(StringSymbol::Comma);
    info.append(this->getTransformedID(connector->getSecondConnectedNode()));
    this->connectionInfoVector.push_back(info);
}

void SaveComponentVisitor::visitComponent(Component* component){
    string info;
    info.append(component->getType());
    if(component->getName() != StringSymbol::Empty){
        info.append(StringSymbol::Comma);
        info.append(StringSymbol::Space);
        info.append(component->getName());
    }
    this->componentInfoVector.push_back(info);
}