#include "RelationShip.h"
#include "ComponentUtil.h"
#include "ERModel.h"
#include "Attribute.h"
#include "Entity.h"
#include "StringUtil.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentConnectionSize.h"

RelationShip::RelationShip(string componentID,string componentName) : Node(ComponentType::TypeRelationShip,componentID,componentName){
}

RelationShip::~RelationShip(){
}

int RelationShip::canConnectTo(Component* target){
    int canConnect = Node::canConnectTo(target);

    if(target->isTypeOf<Attribute>())
        throw InvalidConnectException(this->getID(),target->getID());
    else if(target->isTypeOf<Entity>())
        canConnect = NodeConnectionType::ConnectEntityAndRelation;

    return canConnect;
}

bool RelationShip::hasSizeToConnect(){
    return this->getAllConnections().size() < ComponentConnectionSize::RelationShipConnectionSize;
}

bool RelationShip::isRelationType(string relationType){
    if(this->hasSizeToConnect())
        return false;
    
    bool isRType = true;
    if(relationType == RelationType::One){
        for each(Component* component in this->getAllConnections())
            isRType &= (component->getName() == RelationType::One);
    }
    else{
        isRType = false;
    }
    
    return isRType;
}
//get related Entity
HashMap<string,Entity*> RelationShip::getConnectedEntities(){
    return ComponentUtil::getConnectedNodeHashMapByType<Entity>(this->getAllConnections());
}

Component* RelationShip::clone() const{
    return new RelationShip(*this);
}