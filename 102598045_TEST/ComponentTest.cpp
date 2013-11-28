#include "ComponentTest.h"
#include "ComponentType.h"
#include "ComponentUtil.h"

void ComponentTest::SetUp(){
    this->attribute = new Attribute("0");
    this->relationShip = new RelationShip("1");
    this->entity = new Entity("2");

    this->connector = new Connector("3");
    ComponentUtil::connectWithEachOther(this->attribute,this->entity,this->connector);
}

void ComponentTest::TearDown(){
    delete this->attribute;
    delete this->entity;
    delete this->relationShip;
    delete this->connector;
}

TEST_F(ComponentTest,testGetClassName){
    ASSERT_EQ(ComponentType::TypeAttributeName,this->attribute->getClassName());
    ASSERT_EQ(ComponentType::TypeRelationShipName,this->relationShip->getClassName());
    ASSERT_EQ(ComponentType::TypeEntityName,this->entity->getClassName());
    ASSERT_EQ(ComponentType::TypeConnectorName,this->connector->getClassName());
}

TEST_F(ComponentTest,testIsTypeOf){
}

TEST_F(ComponentTest,testConnectTo){
    ASSERT_EQ(1,this->attribute->getAllConnections().size());
    ASSERT_EQ(true,this->attribute->getAllConnections().containsKey("3"));
    
    this->attribute->connectTo(this->connector);
    ASSERT_EQ(1,this->attribute->getAllConnections().size());

    ASSERT_EQ(1,this->entity->getAllConnections().size());
    ASSERT_EQ(0,this->relationShip->getAllConnections().size());
    this->entity->connectTo(this->relationShip);
    ASSERT_EQ(2,this->entity->getAllConnections().size());
    ASSERT_EQ(0,this->relationShip->getAllConnections().size());
}

TEST_F(ComponentTest,testDisconnectTo){
    ASSERT_EQ(1,this->attribute->getAllConnections().size());
    ASSERT_EQ(true,this->attribute->getAllConnections().containsKey("3"));
    
    this->attribute->disconnectTo(this->entity);
    ASSERT_EQ(1,this->attribute->getAllConnections().size());

    this->attribute->disconnectTo(this->connector);
    ASSERT_EQ(0,this->attribute->getAllConnections().size());
}

TEST_F(ComponentTest,testHasConnectedTo){
}