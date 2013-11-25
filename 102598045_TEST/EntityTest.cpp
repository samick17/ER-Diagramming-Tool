#include "EntityTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "EmptyCollectionException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"
#include "NoConnectionException.h"
#include "StringSymbol.h"
#include "ComponentUtil.h"

void EntityTest::SetUp(){
    this->attribute = new Attribute("0","Name");
    this->relationShip = new RelationShip("1","Has");
    this->entity = new Entity("2","Engineer");
}

void EntityTest::TearDown(){
    delete this->attribute;
    delete this->relationShip;
    delete this->entity;
}

TEST_F(EntityTest,testGetType){
    ASSERT_EQ(ComponentType::TypeEntity,this->entity->getType());
}

TEST_F(EntityTest,testCanConnectTo){
    ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(this->attribute));
    ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(this->relationShip));
    
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);
    Connector connector2("4");
    ComponentUtil::connectWithEachOther(this->entity,this->relationShip,&connector2);

    ASSERT_THROW(this->entity->canConnectTo(this->entity),ConnectedSelfException);
    ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
    ASSERT_THROW(this->entity->canConnectTo(this->relationShip),HasConnectedException);
    ASSERT_THROW(this->entity->canConnectTo(&Entity("5")),InvalidConnectException);
    ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(&Attribute("6")));
    ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(&RelationShip("7")));
}

TEST_F(EntityTest,testGetConnectedAttributes){
    ASSERT_EQ(0,this->entity->getConnectedAttributes().size());

    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);

    ASSERT_EQ(1,this->entity->getConnectedAttributes().size());

    ASSERT_EQ(this->attribute,this->entity->getConnectedAttributes().get(this->attribute->getID()));
}

TEST_F(EntityTest,testGetAttributeByID){
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);
    ASSERT_THROW(this->entity->getAttributeByID("100"),NoConnectionException);
    ASSERT_EQ(this->attribute,this->entity->getAttributeByID(this->attribute->getID()));
}

TEST_F(EntityTest,testGetPrimaryKeyAttributes){
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);

    ASSERT_EQ(0,this->entity->getPrimaryKeyAttributes().size());

    this->entity->setPrimaryKey("0");

    ASSERT_EQ(1,this->entity->getPrimaryKeyAttributes().size());
    ASSERT_EQ(this->attribute,this->entity->getPrimaryKeyAttributes().get(this->attribute->getID()));
}

TEST_F(EntityTest,testSetPrimaryKey){
    ASSERT_THROW(this->entity->setPrimaryKey("1"),NoConnectionException);
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);

    ASSERT_EQ(false,(static_cast<Attribute*>(this->attribute)->isPrimaryKey()));

    ASSERT_THROW(this->entity->setPrimaryKey("1"),NoConnectionException);
    this->entity->setPrimaryKey(this->attribute->getID());
    ASSERT_EQ(true,(static_cast<Attribute*>(this->attribute)->isPrimaryKey()));
}