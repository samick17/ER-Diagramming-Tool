#include "ConnectorTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"

void ConnectorTest::SetUp(){
	Component* attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* relation = this->erModel.addNode(ComponentType::TypeRelationShip);
	Component* entity = this->erModel.addNode(ComponentType::TypeEntity);

	this->erModel.addConnection(attribute,entity);
	this->connector = this->erModel.getNodesConnector(attribute,entity);
}

void ConnectorTest::TearDown(){
	this->connector = NULL;
}

TEST_F(ConnectorTest,testToString){
	ASSERT_EQ("3 0,2",this->connector->toString());
}

TEST_F(ConnectorTest,testGetType){
	ASSERT_EQ(ComponentType::TypeConnector,this->connector->getType());
}

TEST_F(ConnectorTest,testBreakAllConnections){
	//assert connection size
	ASSERT_EQ(2,this->connector->connectionMap.size());
	Component* firstConnectedNode = this->connector->getFirstConnectedNode();
	Component* secondConnectedNode = this->connector->getSecondConnectedNode();
	//assert have connection
	ASSERT_EQ(this->connector,firstConnectedNode->connectionMap.get(this->connector->getID()));
	ASSERT_EQ(this->connector,secondConnectedNode->connectionMap.get(this->connector->getID()));
	//assert break connection
	this->connector->breakAllConnections();
	
	ASSERT_EQ(0,this->connector->connectionMap.size());
}

TEST_F(ConnectorTest,testCanConnectTo){

	Component* attribute = this->erModel.getComponentByID("0");
	Component* relation = this->erModel.getComponentByID("1");
	Component* entity = this->erModel.getComponentByID("2");

	ASSERT_THROW(this->connector->canConnectTo(attribute),InvalidConnectException);
	ASSERT_THROW(this->connector->canConnectTo(relation),InvalidConnectException);
	ASSERT_THROW(this->connector->canConnectTo(entity),InvalidConnectException);
	ASSERT_THROW(this->connector->canConnectTo(this->connector),InvalidConnectException);
}

TEST_F(ConnectorTest,testHasSizeToConnect){
	//will always false, because connector will always construct when need to connect two node.
	ASSERT_EQ(false,this->connector->hasSizeToConnect());
}

TEST_F(ConnectorTest,testGetFirstConnectedNode){
	Component* attribute = this->erModel.getComponentByID("0");
	Component* relation = this->erModel.getComponentByID("1");
	Component* entity = this->erModel.getComponentByID("2");
	this->erModel.addConnection(entity,relation);
	Connector* connectorEntityAndRelation = this->erModel.getNodesConnector(relation,entity);
	
	ASSERT_EQ(attribute,this->connector->getFirstConnectedNode());
	ASSERT_EQ(relation,connectorEntityAndRelation->getFirstConnectedNode());

}

TEST_F(ConnectorTest,testGetSecondConnectedNode){
	Component* attribute = this->erModel.getComponentByID("0");
	Component* relation = this->erModel.getComponentByID("1");
	Component* entity = this->erModel.getComponentByID("2");
	this->erModel.addConnection(entity,relation);
	Connector* connectorEntityAndRelation = this->erModel.getNodesConnector(relation,entity);

	ASSERT_EQ(entity,this->connector->getSecondConnectedNode());
	ASSERT_EQ(entity,connectorEntityAndRelation->getSecondConnectedNode());
}

TEST_F(ConnectorTest,testIsNodesConnection){	
	Component* attribute = this->erModel.getComponentByID("0");
	Component* relation = this->erModel.getComponentByID("1");
	Component* entity = this->erModel.getComponentByID("2");

	ASSERT_EQ(false,this->connector->isNodesConnection(NULL,NULL));
	ASSERT_EQ(false,this->connector->isNodesConnection(attribute,NULL));
	ASSERT_EQ(false,this->connector->isNodesConnection(NULL,attribute));
	ASSERT_EQ(false,this->connector->isNodesConnection(entity,NULL));
	ASSERT_EQ(false,this->connector->isNodesConnection(NULL,entity));
	ASSERT_EQ(false,this->connector->isNodesConnection(attribute,relation));
	ASSERT_EQ(false,this->connector->isNodesConnection(relation,attribute));
	ASSERT_EQ(false,this->connector->isNodesConnection(entity,relation));
	ASSERT_EQ(false,this->connector->isNodesConnection(relation,entity));

	ASSERT_EQ(true,this->connector->isNodesConnection(attribute,entity));
	ASSERT_EQ(true,this->connector->isNodesConnection(entity,attribute));
}

TEST_F(ConnectorTest,testClone){
	Connector* connectorCloned = static_cast<Connector*>(this->connector->clone());

	ASSERT_EQ(this->connector->getID(),connectorCloned->getID());
	ASSERT_EQ(this->connector->getName(),connectorCloned->getName());
	ASSERT_EQ(this->connector->getType(),connectorCloned->getType());
	//assert map
	ASSERT_EQ(this->connector->componentData,connectorCloned->componentData);

	delete connectorCloned;
}