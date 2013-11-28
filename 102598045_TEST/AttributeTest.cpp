#include "AttributeTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"
#include "ComponentUtil.h"
#include "AttributeType.h"

void AttributeTest::SetUp(){
    this->attribute = new Attribute("0","Name");
    this->relationShip = new RelationShip("1","Has");
    this->entity = new Entity("2","Engineer");
}

void AttributeTest::TearDown(){
    delete this->attribute;
    delete this->relationShip;
    delete this->entity;
}

TEST_F(AttributeTest,testGetType){
    ASSERT_EQ(ComponentType::TypeAttribute,this->attribute->getType());
}

TEST_F(AttributeTest,testCanConnectTo){
    ASSERT_THROW(this->attribute->canConnectTo(this->relationShip),InvalidConnectException);
    ASSERT_EQ(NodeConnectionType::ValidConnect,this->attribute->canConnectTo(this->entity));
    ASSERT_THROW(this->attribute->canConnectTo(this->attribute),ConnectedSelfException);

    Connector connector("3");
    ComponentUtil::connectWithEachOther(this->attribute,this->entity,&connector);

    ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);
    ASSERT_THROW(this->attribute->canConnectTo(&Attribute("10")),InvalidConnectException);
    ASSERT_THROW(this->attribute->canConnectTo(&Entity("27")),InvalidConnectException);
}
TEST_F(AttributeTest,testHasSizeToConnect){
    ASSERT_EQ(true,this->attribute->hasSizeToConnect());

    Connector connector("3");
    ComponentUtil::connectWithEachOther(this->attribute,this->entity,&connector);
    ASSERT_EQ(false,this->attribute->hasSizeToConnect());
}

TEST_F(AttributeTest,testIsPrimaryKey){
    ASSERT_EQ(false,this->attribute->isPrimaryKey());
    this->attribute->setAsPrimaryKey();
    ASSERT_EQ(true,this->attribute->isPrimaryKey());
}

TEST_F(AttributeTest,testSetAsPrimaryKey){
    ASSERT_EQ(AttributeType::Default,this->attribute->attributeType);
    this->attribute->setAsPrimaryKey();
    ASSERT_EQ(AttributeType::PrimaryKey,this->attribute->attributeType);
}

TEST_F(AttributeTest,testSetAsDefaultKey){
    this->attribute->attributeType = AttributeType::PrimaryKey;
    this->attribute->setAsDefaultKey();
    ASSERT_EQ(AttributeType::Default,this->attribute->attributeType);
}