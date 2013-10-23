#include "ComponentUtilTest.h"

#include "ComponentUtil.h"

void ComponentUtilTest::SetUp(){
	this->attribute = new Attribute(ComponentData("57",""));
	this->entity = new Entity(ComponentData("18",""));
	this->relationShip = new RelationShip(ComponentData("32",""));
	this->connector1 = new Connector(ComponentData("19",""));
	this->connector2 = new Connector(ComponentData("37",""));
}

void ComponentUtilTest::TearDown(){
	delete this->attribute;
	delete this->entity;
	delete this->relationShip;
	delete this->connector1;
	delete this->connector2;
}

TEST_F(ComponentUtilTest,testGetConnectedNodeHashMapByType){
	this->attribute->connectTo(connector1);
	this->entity->connectTo(connector1);	
	this->connector1->connectTo(attribute);	
	this->connector1->connectTo(entity);

	ASSERT_EQ(1,ComponentUtil::getConnectedNodeHashMapByType<Attribute>(this->entity->getAllConnections()).size());
	ASSERT_EQ(this->attribute,ComponentUtil::getConnectedNodeHashMapByType<Attribute>(this->entity->getAllConnections()).get("57"));	
	ASSERT_EQ(1,ComponentUtil::getConnectedNodeHashMapByType<Entity>(this->attribute->getAllConnections()).size());
	ASSERT_EQ(this->entity,ComponentUtil::getConnectedNodeHashMapByType<Entity>(this->attribute->getAllConnections()).get("18"));
	
	this->relationShip->connectTo(this->connector2);
	this->entity->connectTo(this->connector2);	
	this->connector2->connectTo(this->relationShip);	
	this->connector2->connectTo(this->entity);

	ASSERT_EQ(1,ComponentUtil::getConnectedNodeHashMapByType<RelationShip>(this->entity->getAllConnections()).size());
	ASSERT_EQ(this->relationShip,ComponentUtil::getConnectedNodeHashMapByType<RelationShip>(this->entity->getAllConnections()).get("32"));	
	ASSERT_EQ(1,ComponentUtil::getConnectedNodeHashMapByType<Attribute>(this->entity->getAllConnections()).size());
	ASSERT_EQ(this->attribute,ComponentUtil::getConnectedNodeHashMapByType<Attribute>(this->entity->getAllConnections()).get("57"));	
	ASSERT_EQ(1,ComponentUtil::getConnectedNodeHashMapByType<Entity>(this->relationShip->getAllConnections()).size());
	ASSERT_EQ(this->entity,ComponentUtil::getConnectedNodeHashMapByType<Entity>(this->relationShip->getAllConnections()).get("18"));	
}


TEST_F(ComponentUtilTest,testToComponentHashMap){
}

TEST_F(ComponentUtilTest,testConnectWithEachOther){
	//Assert initial size
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	ASSERT_EQ(0,this->connector1->getAllConnections().size());
	ASSERT_EQ(0,this->connector2->getAllConnections().size());
	
	ComponentUtil::connectWithEachOther(this->attribute,this->entity,this->connector1);
	//Assert size after connect each other
	ASSERT_EQ(1,this->attribute->getAllConnections().size());
	ASSERT_EQ(1,this->entity->getAllConnections().size());
	ASSERT_EQ(2,this->connector1->getAllConnections().size());
	//Assert connected components
	ASSERT_EQ(this->attribute,this->connector1->getAllConnections().get("57"));
	ASSERT_EQ(this->entity,this->connector1->getAllConnections().get("18"));
	ASSERT_EQ(this->connector1,this->attribute->getAllConnections().get("19"));
	ASSERT_EQ(this->connector1,this->entity->getAllConnections().get("19"));
	
	ComponentUtil::connectWithEachOther(this->relationShip,this->entity,this->connector2);
	//Assert size after connect each other
	ASSERT_EQ(1,this->relationShip->getAllConnections().size());
	ASSERT_EQ(2,this->entity->getAllConnections().size());
	ASSERT_EQ(2,this->connector2->getAllConnections().size());
	//Assert connected components
	ASSERT_EQ(this->relationShip,this->connector2->getAllConnections().get("32"));
	ASSERT_EQ(this->entity,this->connector2->getAllConnections().get("18"));
	ASSERT_EQ(this->connector2,this->relationShip->getAllConnections().get("37"));
	ASSERT_EQ(this->connector2,this->entity->getAllConnections().get("37"));
}

TEST_F(ComponentUtilTest,testDisconnectWithEachOther){
	//Assert initial size
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	ASSERT_EQ(0,this->connector1->getAllConnections().size());
	ASSERT_EQ(0,this->connector2->getAllConnections().size());

	//Connect with each other
	this->attribute->connectTo(this->connector1);
	this->entity->connectTo(this->connector1);	
	this->connector1->connectTo(this->attribute);	
	this->connector1->connectTo(this->entity);
	//Assert size after connect
	ASSERT_EQ(1,this->attribute->getAllConnections().size());
	ASSERT_EQ(1,this->entity->getAllConnections().size());
	ASSERT_EQ(2,this->connector1->getAllConnections().size());
	//assert connected component
	ASSERT_EQ(this->attribute,this->connector1->getAllConnections().get("57"));
	ASSERT_EQ(this->entity,this->connector1->getAllConnections().get("18"));
	ASSERT_EQ(this->connector1,this->attribute->getAllConnections().get("19"));
	ASSERT_EQ(this->connector1,this->entity->getAllConnections().get("19"));

	ComponentUtil::disconnectWithEachOther(this->attribute,this->entity,this->connector1);
	//Assert size after disconnect
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());
	ASSERT_EQ(0,this->connector1->getAllConnections().size());
	//Connect with each other
	this->relationShip->connectTo(this->connector2);
	this->entity->connectTo(this->connector2);	
	this->connector2->connectTo(this->relationShip);	
	this->connector2->connectTo(this->entity);
	//Assert size after connect
	ASSERT_EQ(1,this->relationShip->getAllConnections().size());
	ASSERT_EQ(1,this->entity->getAllConnections().size());
	ASSERT_EQ(2,this->connector2->getAllConnections().size());
	//assert connected component
	ASSERT_EQ(this->relationShip,this->connector2->getAllConnections().get("32"));
	ASSERT_EQ(this->entity,this->connector2->getAllConnections().get("18"));
	ASSERT_EQ(this->connector2,this->relationShip->getAllConnections().get("37"));
	ASSERT_EQ(this->connector2,this->entity->getAllConnections().get("37"));

	ComponentUtil::disconnectWithEachOther(this->relationShip,this->entity,this->connector2);
	
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());
	ASSERT_EQ(0,this->connector2->getAllConnections().size());
}