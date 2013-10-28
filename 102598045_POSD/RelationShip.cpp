#include "RelationShip.h"
#include "ComponentUtil.h"
#include "ERModel.h"
#include "Attribute.h"
#include "Entity.h"
#include "StringUtil.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentConnectionSize.h"

RelationShip::RelationShip(ComponentData componentData) : Node(componentData){
}

RelationShip::~RelationShip(){
}

string RelationShip::getType(){
    return ComponentType::TypeRelationShip;
}

int RelationShip::canConnectTo(Component* target){
    int canConnect = Node::canConnectTo(target);

    if(typeid(*target).name() == typeid(Attribute).name())
        throw InvalidConnectException(this->getID(),target->getID());    
    else if(typeid(*target).name() == typeid(Entity).name())
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
    if(relationType == RelationType::OneToOne){
        for each(Component* component in this->getAllConnections())        
            isRType &= (component->getName() == RelationType::OneToOne);        
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