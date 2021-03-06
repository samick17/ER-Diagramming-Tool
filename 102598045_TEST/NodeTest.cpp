#include "NodeTest.h"
#include "ComponentType.h"
#include "ConnectedSelfException.h"
#include "InvalidConnectException.h"
#include "HasConnectedException.h"
#include "ComponentUtil.h"

void NodeTest::SetUp(){
    this->attribute = new Attribute("0","Name");
    this->relationShip = new RelationShip("1","Has");
    this->entity = new Entity("2","Engineer");
}

void NodeTest::TearDown(){
    delete this->attribute;
    delete this->relationShip;
    delete this->entity;
}

TEST_F(NodeTest,testBreakAllConnections){
    ASSERT_EQ(0,this->attribute->getAllConnections().size());
    ASSERT_EQ(0,this->relationShip->getAllConnections().size());
    ASSERT_EQ(0,this->entity->getAllConnections().size());

    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->attribute,this->entity,&connector1);
    Connector connector2("4");
    ComponentUtil::connectWithEachOther(this->relationShip,this->entity,&connector2);

    Entity entity2("5");
    Attribute attribute2("6");
    Connector connector3("7");
    ComponentUtil::connectWithEachOther(&attribute2,this->entity,&connector3);
    Connector connector4("8");
    ComponentUtil::connectWithEachOther(this->relationShip,&entity2,&connector4);

    ASSERT_EQ(1,this->attribute->getAllConnections().size());
    ASSERT_EQ(2,this->relationShip->getAllConnections().size());
    ASSERT_EQ(3,this->entity->getAllConnections().size());

    this->attribute->breakAllConnections();
    this->relationShip->breakAllConnections();
    this->entity->breakAllConnections();

    ASSERT_EQ(0,this->attribute->getAllConnections().size());
    ASSERT_EQ(0,this->relationShip->getAllConnections().size());
    ASSERT_EQ(0,this->entity->getAllConnections().size());
}

TEST_F(NodeTest,testCanConnectTo){
    //connect self
    ASSERT_THROW(this->attribute->canConnectTo(this->attribute),ConnectedSelfException);
    ASSERT_THROW(this->entity->canConnectTo(this->entity),ConnectedSelfException);
    ASSERT_THROW(this->relationShip->canConnectTo(this->relationShip),ConnectedSelfException);
    //same type
    ASSERT_THROW(this->attribute->canConnectTo(&Attribute("3")),InvalidConnectException);
    ASSERT_THROW(this->entity->canConnectTo(&Entity("4")),InvalidConnectException);
    ASSERT_THROW(this->relationShip->canConnectTo(&RelationShip("5")),InvalidConnectException);

    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->attribute,this->entity,&connector1);
    Connector connector2("4");
    ComponentUtil::connectWithEachOther(this->relationShip,this->entity,&connector2);
    //has connected
    ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);
    ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
    ASSERT_THROW(this->relationShip->canConnectTo(this->entity),HasConnectedException);
    ASSERT_THROW(this->entity->canConnectTo(this->relationShip),HasConnectedException);

    ASSERT_THROW(this->attribute->canConnectTo(&Entity("6")),InvalidConnectException);

    Entity entity2("7");
    ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->relationShip->canConnectTo(&entity2));

    Connector connector3("8");
    ComponentUtil::connectWithEachOther(&entity2,this->relationShip,&connector3);    
    ASSERT_THROW(this->relationShip->canConnectTo(&Entity("9")),InvalidConnectException);

    ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(&Attribute("10")));
    ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(&RelationShip("11")));
}