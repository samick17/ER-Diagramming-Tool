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
	this->attribute = new Attribute(ComponentData("0","Name"));
	this->relationShip = new RelationShip(ComponentData("1","Has"));
	this->entity = new Entity(ComponentData("2","Engineer"));
}

void EntityTest::TearDown(){
	delete this->attribute;
	delete this->relationShip;
	delete this->entity;
}

TEST_F(EntityTest,testToString){
	ASSERT_EQ(StringSymbol::Empty,this->entity->toString());

	Connector connector1 = Connector(ComponentData("3",""));
	ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);
	this->attribute->setAsPrimaryKey();

	ASSERT_EQ("2 0",this->entity->toString());

	Attribute attribute2 = Attribute(ComponentData("4","ID"));
	Connector connector2 = Connector(ComponentData("5",""));
	ComponentUtil::connectWithEachOther(this->entity,&attribute2,&connector2);
	attribute2.setAsPrimaryKey();

	ASSERT_EQ("2 0,4",this->entity->toString());
}

TEST_F(EntityTest,testGetType){
	ASSERT_EQ(ComponentType::TypeEntity,this->entity->getType());
}

TEST_F(EntityTest,testCanConnectTo){
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(this->attribute));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(this->relationShip));
	
	Connector connector1 = Connector(ComponentData("3",""));
	ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);
	Connector connector2 = Connector(ComponentData("4",""));
	ComponentUtil::connectWithEachOther(this->entity,this->relationShip,&connector2);

	ASSERT_THROW(this->entity->canConnectTo(this->entity),ConnectedSelfException);
	ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->relationShip),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(&Entity(ComponentData("5",""))),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(&Attribute(ComponentData("6",""))));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(&RelationShip(ComponentData("7",""))));
}

TEST_F(EntityTest,testGetConnectedAttributes){
	ASSERT_EQ(0,this->entity->getConnectedAttributes().size());

	Connector connector1 = Connector(ComponentData("3",""));
	ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);

	ASSERT_EQ(1,this->entity->getConnectedAttributes().size());

	ASSERT_EQ(this->attribute,this->entity->getConnectedAttributes().get(this->attribute->getID()));
}

TEST_F(EntityTest,testGetAttributeByID){
	Connector connector1 = Connector(ComponentData("3",""));
	ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);
	ASSERT_THROW(this->entity->getAttributeByID("100"),NoConnectionException);
	ASSERT_EQ(this->attribute,this->entity->getAttributeByID(this->attribute->getID()));
}

TEST_F(EntityTest,testGetPrimaryKeyAttributes){
	Connector connector1 = Connector(ComponentData("3",""));
	ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);

	ASSERT_EQ(0,this->entity->getPrimaryKeyAttributes().size());

	vector<string> primaryKeyID;
	primaryKeyID.push_back("0");
	this->entity->setPrimaryKey(primaryKeyID);

	ASSERT_EQ(1,this->entity->getPrimaryKeyAttributes().size());
	ASSERT_EQ(this->attribute,this->entity->getPrimaryKeyAttributes().get(this->attribute->getID()));
}

TEST_F(EntityTest,testSetPrimaryKey){
	vector<string> primaryKeyID;
	primaryKeyID.push_back("1");
	ASSERT_THROW(this->entity->setPrimaryKey(primaryKeyID),NoConnectionException);
	Connector connector1 = Connector(ComponentData("3",""));
	ComponentUtil::connectWithEachOther(this->entity,this->attribute,&connector1);

	ASSERT_EQ(false,(static_cast<Attribute*>(this->attribute)->isPrimaryKey()));

	ASSERT_THROW(this->entity->setPrimaryKey(primaryKeyID),NoConnectionException);
	primaryKeyID.clear();
	primaryKeyID.push_back("0");
	this->entity->setPrimaryKey(primaryKeyID);
	ASSERT_EQ(true,(static_cast<Attribute*>(this->attribute)->isPrimaryKey()));	
}

TEST_F(EntityTest,testClone){
	Entity entityCloned = *static_cast<Entity*>(this->entity->clone());

	ASSERT_EQ(this->entity->getID(),entityCloned.getID());
	ASSERT_EQ(this->entity->getName(),entityCloned.getName());
	ASSERT_EQ(this->entity->getType(),entityCloned.getType());
	//assert componentData
	ASSERT_EQ(this->entity->componentData,entityCloned.componentData);
}