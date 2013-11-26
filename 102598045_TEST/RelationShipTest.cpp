#include "RelationShipTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"
#include "ComponentUtil.h"

void RelationShipTest::SetUp(){
    this->attribute = new Attribute("0","Name");
    this->relationShip = new RelationShip("1","Has");
    this->entity = new Entity("2","Engineer");
}

void RelationShipTest::TearDown(){
    delete this->attribute;
    delete this->relationShip;
    delete this->entity;
}

TEST_F(RelationShipTest,testGetType){
    ASSERT_EQ(ComponentType::TypeRelationShip,this->relationShip->getType());
}
        
TEST_F(RelationShipTest,CanConnectTo){
    ASSERT_THROW(this->relationShip->canConnectTo(this->attribute),InvalidConnectException);
    ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->relationShip->canConnectTo(this->entity));
    ASSERT_THROW(this->relationShip->canConnectTo(this->relationShip),ConnectedSelfException);

    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->entity,this->relationShip,&connector1);
    ASSERT_THROW(this->relationShip->canConnectTo(this->entity),HasConnectedException);
    ASSERT_THROW(this->relationShip->canConnectTo(&RelationShip("4","WorkOn")),InvalidConnectException);
    Entity entity2("5","PC");
    Connector connector2("6");
    ComponentUtil::connectWithEachOther(&entity2,this->relationShip,&connector2);

    ASSERT_THROW(this->relationShip->canConnectTo(&Entity("7","NoteBook")),InvalidConnectException);
}

TEST_F(RelationShipTest,testHasSizeToConnect){
    ASSERT_EQ(true,this->attribute->hasSizeToConnect());
    ASSERT_EQ(true,this->relationShip->hasSizeToConnect());
    ASSERT_EQ(true,this->entity->hasSizeToConnect());
    //connect and assert has size to connect
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->relationShip,this->entity,&connector1);
    ASSERT_EQ(true,this->relationShip->hasSizeToConnect());

    Entity entity2("4","NoteBook");
    Connector connector2("5");
    ComponentUtil::connectWithEachOther(this->relationShip,&entity2,&connector2);
    ASSERT_EQ(false,this->relationShip->hasSizeToConnect());
}

TEST_F(RelationShipTest,testIsRelationType){
    ASSERT_EQ(false,this->relationShip->isRelationType("X"));
    
    ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::One));
    //assert is correct relation type
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->relationShip,this->entity,&connector1);
    Entity entity2("4","NoteBook");
    Connector connector2("5");
    ComponentUtil::connectWithEachOther(this->relationShip,&entity2,&connector2);
    ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::One));
    connector1.setName(RelationType::One);
    ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::One));
    connector2.setName(RelationType::One);
    ASSERT_EQ(true,this->relationShip->isRelationType(RelationType::One));
}

TEST_F(RelationShipTest,testGetConnectedEntities){
    ASSERT_EQ(0,this->relationShip->getConnectedEntities().size());
    Connector connector1("3");
    ComponentUtil::connectWithEachOther(this->relationShip,this->entity,&connector1);

    ASSERT_EQ(1,this->relationShip->getConnectedEntities().size());
    Entity entity2("4","NoteBook");
    Connector connector2("5");
    ComponentUtil::connectWithEachOther(this->relationShip,&entity2,&connector2);
    ASSERT_EQ(2,this->relationShip->getConnectedEntities().size());
}