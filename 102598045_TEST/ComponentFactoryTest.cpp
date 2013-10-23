#include "ComponentFactoryTest.h"
#include "InvalidNodeTypeException.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"

void ComponentFactoryTest::SetUp(){
	this->componentFactory.resetFactory();
	ASSERT_EQ(0,ComponentFactory::count);
}

void ComponentFactoryTest::TearDown(){
}

TEST_F(ComponentFactoryTest,testCreateComponent){
	ASSERT_THROW(this->componentFactory.createComponent("X"),InvalidNodeTypeException);

	Component* attribute = this->componentFactory.createComponent(ComponentType::TypeAttribute);
	ASSERT_EQ(1,ComponentFactory::count);
	ASSERT_EQ(typeid(Attribute).name(),typeid(*attribute).name());
	ASSERT_EQ(ComponentType::TypeAttribute,attribute->getType());		
	delete attribute;

	Component* entity = this->componentFactory.createComponent(ComponentType::TypeEntity);
	ASSERT_EQ(2,ComponentFactory::count);
	ASSERT_EQ(typeid(Entity).name(),typeid(*entity).name());
	ASSERT_EQ(ComponentType::TypeEntity,entity->getType());	
	delete entity;

	Component* relationShip = this->componentFactory.createComponent(ComponentType::TypeRelationShip);
	ASSERT_EQ(3,ComponentFactory::count);
	ASSERT_EQ(typeid(RelationShip).name(),typeid(*relationShip).name());
	ASSERT_EQ(ComponentType::TypeRelationShip,relationShip->getType());	
	delete relationShip;

	Component* connector = this->componentFactory.createComponent(ComponentType::TypeConnector);
	ASSERT_EQ(4,ComponentFactory::count);
	ASSERT_EQ(typeid(Connector).name(),typeid(*connector).name());
	ASSERT_EQ(ComponentType::TypeConnector,connector->getType());	
	delete connector;
}

TEST_F(ComponentFactoryTest,testFindNewComponentFunction){
	ASSERT_THROW(this->componentFactory.findNewComponentFunction("Z"),InvalidNodeTypeException);
	//test new attribute
	NewComponentFunction newAttributeFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeAttribute);
	Component* attribute = newAttributeFunction(ComponentData("12","Name"));
	ASSERT_EQ(typeid(Attribute).name(),typeid(*attribute).name());
	ASSERT_EQ(ComponentType::TypeAttribute,attribute->getType());	
	ASSERT_EQ("12",attribute->getID());	
	ASSERT_EQ("Name",attribute->getName());	
	//test new entity
	NewComponentFunction newEntityFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeEntity);
	Component* entity = newEntityFunction(ComponentData("200","Character"));
	ASSERT_EQ(typeid(Entity).name(),typeid(*entity).name());
	ASSERT_EQ(ComponentType::TypeEntity,entity->getType());	
	ASSERT_EQ("200",entity->getID());	
	ASSERT_EQ("Character",entity->getName());	
	//test new relationShip
	NewComponentFunction newRelationShipFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeRelationShip);
	Component* relationShip = newRelationShipFunction(ComponentData("109","Owns"));
	ASSERT_EQ(typeid(RelationShip).name(),typeid(*relationShip).name());
	ASSERT_EQ(ComponentType::TypeRelationShip,relationShip->getType());	
	ASSERT_EQ("109",relationShip->getID());	
	ASSERT_EQ("Owns",relationShip->getName());	
	//test new connector
	NewComponentFunction newConnectorFunction = this->componentFactory.findNewComponentFunction(ComponentType::TypeConnector);
	Component* connector = newConnectorFunction(ComponentData("315",RelationType::OneToOne));
	ASSERT_EQ(typeid(Connector).name(),typeid(*connector).name());
	ASSERT_EQ(ComponentType::TypeConnector,connector->getType());	
	ASSERT_EQ("315",connector->getID());	
	ASSERT_EQ(RelationType::OneToOne,connector->getName());	
}