#include "ConnectorTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"

void ConnectorTest::SetUp(){
	this->erModel = ERModel();
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
	ASSERT_EQ(2,this->connector->connectionSet.size());
	Component* firstConnectedNode = this->connector->getFirstConnectedNode();
	Component* secondConnectedNode = this->connector->getSecondConnectedNode();
	//assert have connection
	ASSERT_EQ(this->connector,*(firstConnectedNode->connectionSet.find(this->connector)));
	ASSERT_EQ(this->connector,*(secondConnectedNode->connectionSet.find(this->connector)));
	//assert break connection
	this->connector->breakAllConnections();
	ASSERT_EQ(firstConnectedNode->connectionSet.end(),firstConnectedNode->connectionSet.find(this->connector));
	ASSERT_EQ(secondConnectedNode->connectionSet.end(),secondConnectedNode->connectionSet.find(this->connector));
	ASSERT_EQ(0,this->connector->connectionSet.size());
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

}

TEST_F(ConnectorTest,testClone){
}