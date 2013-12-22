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

void SaveComponentVisitor::visit(Attribute* attribute){
    this->visitComponent(attribute);
}

void SaveComponentVisitor::visit(Entity* entity){
    this->visitComponent(entity);
    string info;
    info.append(entity->getID());
    info.append(StringSymbol::Space);
    vector<string> primaryKeyAttributeIDs;
    for each(Attribute* attribute in entity->getPrimaryKeyAttributes())
        primaryKeyAttributeIDs.push_back(attribute->getID());
    info.append(StringUtil::appendWithComma(primaryKeyAttributeIDs));
    this->primaryKeyInfoVector.push_back(info);
}


void SaveComponentVisitor::visit(RelationShip* relationShip){
    this->visitComponent(relationShip);
}

void SaveComponentVisitor::visit(Connector* connector){
    this->visitComponent(connector);
    string info;
    info.append(connector->getID());
    info.append(StringSymbol::Space);
    info.append(connector->getFirstConnectedNode()->getID());
    info.append(StringSymbol::Comma);
    info.append(connector->getSecondConnectedNode()->getID());
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