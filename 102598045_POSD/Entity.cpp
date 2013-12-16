#include "Entity.h"
#include "Attribute.h"
#include "RelationShip.h"
#include "ComponentUtil.h"
#include "ComponentType.h"
#include "NoConnectionException.h"

Entity::Entity(string componentID,string componentName) : Node(ComponentType::TypeEntity,componentID,componentName){
}

Entity::~Entity(){
}

int Entity::canConnectTo(Component* target){
    int canConnect = Node::canConnectTo(target);

    if(target->isTypeOf<RelationShip>())
        canConnect = NodeConnectionType::ConnectEntityAndRelation;

    return canConnect;
}

HashMap<string,Attribute*> Entity::getConnectedAttributes(){
    HashMap<string,Attribute*> connectedAttributeMap = ComponentUtil::getConnectedNodeHashMapByType<Attribute>(this->getAllConnections());
    return connectedAttributeMap;
}
//get Attribute By ID, if doesn't has such attribute, throw exception
Attribute* Entity::getAttributeByID(string id){
    HashMap<string,Attribute*> attributeMap = this->getConnectedAttributes();
    for each(Attribute* attribute in attributeMap)
        if(attribute->getID() == id)
            return attribute;
    throw NoConnectionException(id);
}

HashMap<string,Attribute*> Entity::getPrimaryKeyAttributes(){
    HashMap<string,Attribute*> attributeMap;
    for each(Attribute* attribute in this->getConnectedAttributes()){
        if(attribute->isPrimaryKey())
            attributeMap.put(attribute->getID(),attribute);
    }
    return attributeMap;
}

void Entity::setPrimaryKey(string componentID){
    Attribute* attribute = this->getAttributeByID(componentID);
    attribute->setAsPrimaryKey();
}

Component* Entity::clone(){
    return new Entity(*this);
}