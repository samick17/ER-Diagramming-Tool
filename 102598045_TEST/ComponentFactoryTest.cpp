#include "ComponentFactoryTest.h"
#include "InvalidNodeTypeException.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"

void ComponentFactoryTest::SetUp(){
}

void ComponentFactoryTest::TearDown(){
}

TEST_F(ComponentFactoryTest,testCreateComponent){
    ASSERT_THROW(this->componentFactory.createComponent("X","0"),InvalidNodeTypeException);

    Component* attribute = this->componentFactory.createComponent(ComponentType::TypeAttribute,"1");
    ASSERT_EQ(typeid(Attribute).name(),typeid(*attribute).name());
    ASSERT_EQ(ComponentType::TypeAttribute,attribute->getType());
    delete attribute;

    Component* entity = this->componentFactory.createComponent(ComponentType::TypeEntity,"2");
    ASSERT_EQ(typeid(Entity).name(),typeid(*entity).name());
    ASSERT_EQ(ComponentType::TypeEntity,entity->getType());
    delete entity;

    Component* relationShip = this->componentFactory.createComponent(ComponentType::TypeRelationShip,"3");
    ASSERT_EQ(typeid(RelationShip).name(),typeid(*relationShip).name());
    ASSERT_EQ(ComponentType::TypeRelationShip,relationShip->getType());
    delete relationShip;

    Component* connector = this->componentFactory.createComponent(ComponentType::TypeConnector,"4");
    ASSERT_EQ(typeid(Connector).name(),typeid(*connector).name());
    ASSERT_EQ(ComponentType::TypeConnector,connector->getType());
    delete connector;
}

TEST_F(ComponentFactoryTest,testFindNewComponentFunction){
    ASSERT_THROW(this->componentFactory.findNewComponentFunction("Z"),InvalidNodeTypeException);
    //test new attribute
    NewComponentFunction newAttributeFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeAttribute);
    Component* attribute = newAttributeFunction("12","Name");
    ASSERT_EQ(typeid(Attribute).name(),typeid(*attribute).name());
    ASSERT_EQ(ComponentType::TypeAttribute,attribute->getType());
    ASSERT_EQ("12",attribute->getID());
    ASSERT_EQ("Name",attribute->getName());
    //test new entity
    NewComponentFunction newEntityFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeEntity);
    Component* entity = newEntityFunction("200","Character");
    ASSERT_EQ(typeid(Entity).name(),typeid(*entity).name());
    ASSERT_EQ(ComponentType::TypeEntity,entity->getType()); 
    ASSERT_EQ("200",entity->getID());    
    ASSERT_EQ("Character",entity->getName());
    //test new relationShip
    NewComponentFunction newRelationShipFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeRelationShip);
    Component* relationShip = newRelationShipFunction("109","Owns");
    ASSERT_EQ(typeid(RelationShip).name(),typeid(*relationShip).name());
    ASSERT_EQ(ComponentType::TypeRelationShip,relationShip->getType());
    ASSERT_EQ("109",relationShip->getID());
    ASSERT_EQ("Owns",relationShip->getName());
    //test new connector
    NewComponentFunction newConnectorFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeConnector);
    Component* connector = newConnectorFunction("315",RelationType::One);
    ASSERT_EQ(typeid(Connector).name(),typeid(*connector).name());
    ASSERT_EQ(ComponentType::TypeConnector,connector->getType());
    ASSERT_EQ("315",connector->getID());
    ASSERT_EQ(RelationType::One,connector->getName());
}