#include "Entity.h"
#include "ERModel.h"
#include "Attribute.h"
#include "RelationShip.h"
#include "ComponentUtil.h"
#include "ComponentType.h"
#include "StringUtil.h"
#include "NoConnectionException.h"
#include "EmptyCollectionException.h"
#include "StringSymbol.h"

Entity::Entity(string componentID) : Node(componentID,ComponentType::TypeEntity){
}

Entity::~Entity(){
}

int Entity::canConnectTo(Component* target){
    int canConnect = Node::canConnectTo(target);
    
    if(typeid(*target).name() == typeid(RelationShip).name())
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

    throw NoConnectionException(id,this->getID());
}

HashMap<string,Attribute*> Entity::getPrimaryKeyAttributes(){
    HashMap<string,Attribute*> attributeMap;
    for each(Attribute* attribute in this->getConnectedAttributes()){
        if(attribute->isPrimaryKey())
            attributeMap.put(attribute->getID(),attribute);
    }
    return attributeMap;
}
//set this primary key by primary key collection, if doesn't has such attribute, throw exception
void Entity::setPrimaryKey(vector<string> primaryKeyIDVector){
    for each(string attributeID in primaryKeyIDVector)
        this->getAttributeByID(attributeID);
    for each(string attributeID in primaryKeyIDVector){
        Attribute* attribute = this->getAttributeByID(attributeID);
        attribute->setAsPrimaryKey();
    }
}