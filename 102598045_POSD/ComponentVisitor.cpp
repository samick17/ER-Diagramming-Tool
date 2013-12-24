#include "ComponentVisitor.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "Component.h"
#include "StringUtil.h"

ComponentVisitor::ComponentVisitor(){
    this->currentVisitIndex = 0;
}

ComponentVisitor::~ComponentVisitor(){
}

void ComponentVisitor::visit(Attribute* attribute){
    this->preVisit(attribute);
    this->doVisit(attribute);
}

void ComponentVisitor::visit(Entity* entity){
    this->preVisit(entity);
    this->doVisit(entity);
}

void ComponentVisitor::visit(RelationShip* relationShip){
    this->preVisit(relationShip);
    this->doVisit(relationShip);
}

void ComponentVisitor::visit(Connector* connector){
    this->preVisit(connector);
    this->doVisit(connector);
}

string ComponentVisitor::getTransformedID(Component* component){
    return this->reorderedIDMap.get(component->getID());
}

void ComponentVisitor::preVisit(Component* component){
    this->reorderedIDMap.put(component->getID(),StringUtil::intToString(this->currentVisitIndex));
    this->currentVisitIndex++;
}