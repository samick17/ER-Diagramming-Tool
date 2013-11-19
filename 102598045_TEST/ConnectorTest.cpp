#include "ConnectorTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ComponentUtil.h"

void ConnectorTest::SetUp(){
    this->attribute = new Attribute("0");
    this->relationShip = new RelationShip("1");
    this->entity = new Entity("2");

    this->connector = new Connector("3");
    ComponentUtil::connectWithEachOther(this->attribute,this->entity,this->connector);
    //ASSERT Connected With Each Other
    ASSERT_EQ(this->attribute,this->connector->getFirstConnectedNode());
    ASSERT_EQ(this->entity,this->connector->getSecondConnectedNode());
    ASSERT_EQ(true,this->attribute->getAllConnections().containsValue(this->connector));
    ASSERT_EQ(true,this->entity->getAllConnections().containsValue(this->connector));
}

void ConnectorTest::TearDown(){
    delete this->attribute;
    delete this->relationShip;
    delete this->entity;
    delete this->connector;
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
    ASSERT_THROW(this->connector->canConnectTo(this->attribute),InvalidConnectException);
    ASSERT_THROW(this->connector->canConnectTo(this->relationShip),InvalidConnectException);
    ASSERT_THROW(this->connector->canConnectTo(this->entity),InvalidConnectException);
    ASSERT_THROW(this->connector->canConnectTo(this->connector),InvalidConnectException);
}

TEST_F(ConnectorTest,testHasSizeToConnect){
    //will always false, because connector will always construct when need to connect two node.
    ASSERT_EQ(false,this->connector->hasSizeToConnect());
}

TEST_F(ConnectorTest,testGetFirstConnectedNode){
    Connector connectorEntityAndRelation("4");
    ASSERT_EQ(NULL,connectorEntityAndRelation.getFirstConnectedNode());
    ASSERT_EQ(NULL,connectorEntityAndRelation.getSecondConnectedNode());

    ComponentUtil::connectWithEachOther(this->entity,this->relationShip,&connectorEntityAndRelation);
    ASSERT_EQ(this->entity,connectorEntityAndRelation.getFirstConnectedNode());
    ASSERT_EQ(this->relationShip,connectorEntityAndRelation.getSecondConnectedNode());
}

TEST_F(ConnectorTest,testGetSecondConnectedNode){
    Connector connectorEntityAndRelation("10");
    ASSERT_EQ(NULL,connectorEntityAndRelation.getFirstConnectedNode());
    ASSERT_EQ(NULL,connectorEntityAndRelation.getSecondConnectedNode());

    ComponentUtil::connectWithEachOther(this->entity,this->relationShip,&connectorEntityAndRelation);
    ASSERT_EQ(this->entity,connectorEntityAndRelation.getFirstConnectedNode());
    ASSERT_EQ(this->relationShip,connectorEntityAndRelation.getSecondConnectedNode());
}

TEST_F(ConnectorTest,testIsNodesConnection){
    ASSERT_EQ(false,this->connector->isNodesConnection(this->attribute,this->relationShip));
    ASSERT_EQ(false,this->connector->isNodesConnection(this->relationShip,this->attribute));
    ASSERT_EQ(false,this->connector->isNodesConnection(this->entity,this->relationShip));
    ASSERT_EQ(false,this->connector->isNodesConnection(this->relationShip,this->entity));

    ASSERT_EQ(true,this->connector->isNodesConnection(this->attribute,this->entity));
    ASSERT_EQ(true,this->connector->isNodesConnection(this->entity,this->attribute));
}