#include "ConnectorTest.h"

void ConnectorTest::SetUp(){
	this->connector = new Connector(ComponentData("0",""));
}

void ConnectorTest::TearDown(){
	delete this->connector;
	this->connector = NULL;
}

TEST_F(ConnectorTest,testToString){
}

TEST_F(ConnectorTest,testGetType){
}

TEST_F(ConnectorTest,testBreakAllConnections){
}

TEST_F(ConnectorTest,testCanConnectTo){
}

TEST_F(ConnectorTest,testHasSizeToConnect){
}

TEST_F(ConnectorTest,testGetFirstConnectedNode){
}

TEST_F(ConnectorTest,testGetSecondConnectedNode){
}

TEST_F(ConnectorTest,testIsNodesConnection){
}

TEST_F(ConnectorTest,testClone){
}