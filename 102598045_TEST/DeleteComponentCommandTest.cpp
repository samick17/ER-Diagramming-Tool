#include "DeleteComponentCommandTest.h"
#include "DeleteComponentCommand.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"
#include "Component.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"

void DeleteComponentCommandTest::SetUp(){
    Component* entity1 = new Entity("0");
    this->componentMap.put(entity1->getID(),entity1);
    Component* attribute1 = new Attribute("1");
    this->componentMap.put(attribute1->getID(),attribute1);
    Component* attribute2 = new Attribute("2");
    this->componentMap.put(attribute2->getID(),attribute2);
    Component* attribute3 = new Attribute("3");
    this->componentMap.put(attribute3->getID(),attribute3);
    this->connectTwoNodes("4",entity1,attribute1);
    this->connectTwoNodes("5",entity1,attribute2);
    this->connectTwoNodes("6",entity1,attribute3);
    Component* relationShip = new RelationShip("7");
    this->componentMap.put(relationShip->getID(),relationShip);
    this->connectTwoNodes("8",entity1,relationShip);
    Component* attribute4 = new Attribute("9");
    this->componentMap.put(attribute4->getID(),attribute4);
    Component* attribute5 = new Attribute("10");
    this->componentMap.put(attribute5->getID(),attribute5);
    Component* attribute6 = new Attribute("11");
    this->componentMap.put(attribute6->getID(),attribute6);
    Component* attribute7 = new Attribute("12");
    this->componentMap.put(attribute7->getID(),attribute7);
    Component* entity2 = new Entity("13");
    this->componentMap.put(entity2->getID(),entity2);
    this->connectTwoNodes("14",entity2,attribute4);
    this->connectTwoNodes("15",entity2,attribute5);
    this->connectTwoNodes("16",entity2,attribute6);
    this->connectTwoNodes("17",entity2,attribute7);
    this->connectTwoNodes("18",entity2,relationShip);
    ASSERT_EQ(19,this->componentMap.size());
}

void DeleteComponentCommandTest::TearDown(){
    for each(Component* component in this->componentMap){
        delete component;
    }
    this->componentMap.clear();
}

void DeleteComponentCommandTest::connectTwoNodes(string componentID,Component* sourceComponent,Component* targetComponent){
    Connector* connector = new Connector(componentID);
    connector->connectTo(sourceComponent);
    connector->connectTo(targetComponent);
    sourceComponent->connectTo(connector);
    targetComponent->connectTo(connector);
    this->componentMap.put(connector->getID(),connector);
}


TEST_F(DeleteComponentCommandTest,testExecute){
    //test delete attribute
    DeleteComponentCommand deleteAttributeCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("1"));
    deleteAttributeCommand.execute();
    ASSERT_EQ(17,this->componentMap.size());
    //test delete entity
    DeleteComponentCommand deleteEntityCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("0"));
    deleteEntityCommand.execute();
    ASSERT_EQ(13,this->componentMap.size());
    //test delete relationShip
    DeleteComponentCommand deleteRelationShipCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("7"));
    deleteRelationShipCommand.execute();
    ASSERT_EQ(11,this->componentMap.size());
    //test delete connector
    DeleteComponentCommand deleteConnectorCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("15"));
    deleteConnectorCommand.execute();
    ASSERT_EQ(10,this->componentMap.size());
}

TEST_F(DeleteComponentCommandTest,testUnexecute){
    //test delete attribute
    DeleteComponentCommand deleteAttributeCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("1"));
    deleteAttributeCommand.clearConnectionDataMap();
    deleteAttributeCommand.removeAndDisconnectComponents();
    ASSERT_EQ(17,this->componentMap.size());
    //test unexecute
    deleteAttributeCommand.executionFlag = true;
    deleteAttributeCommand.unExecute();
    ASSERT_EQ(19,this->componentMap.size());

    //test delete entity
    DeleteComponentCommand deleteEntityCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("0"));
    deleteEntityCommand.clearConnectionDataMap();
    deleteEntityCommand.removeAndDisconnectComponents();
    ASSERT_EQ(14,this->componentMap.size());
    //test unexecute
    deleteEntityCommand.executionFlag = true;
    deleteEntityCommand.unExecute();
    ASSERT_EQ(19,this->componentMap.size());

    //test delete relationShip
    DeleteComponentCommand deleteRelationShipCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("7"));
    deleteRelationShipCommand.clearConnectionDataMap();
    deleteRelationShipCommand.removeAndDisconnectComponents();
    ASSERT_EQ(16,this->componentMap.size());
    //test unexecute
    deleteRelationShipCommand.executionFlag = true;
    deleteRelationShipCommand.unExecute();
    ASSERT_EQ(19,this->componentMap.size());

    //test delete connector
    DeleteComponentCommand deleteConnectorCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("15"));
    deleteConnectorCommand.clearConnectionDataMap();
    deleteConnectorCommand.removeAndDisconnectComponents();
    ASSERT_EQ(18,this->componentMap.size());
    //test unexecute
    deleteConnectorCommand.executionFlag = true;
    deleteConnectorCommand.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
}

TEST_F(DeleteComponentCommandTest,testDeleteComponentCommand){
    //delete entity
    DeleteComponentCommand deleteComponnentCommand1 = DeleteComponentCommand(this->componentMap,this->componentMap.get("0"));
    ASSERT_EQ(4,deleteComponnentCommand1.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand1.execute();
    ASSERT_EQ(14,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand1.component->getAllConnections().size());
    deleteComponnentCommand1.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(4,deleteComponnentCommand1.component->getAllConnections().size());
    deleteComponnentCommand1.execute();
    ASSERT_EQ(14,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand1.component->getAllConnections().size());
    deleteComponnentCommand1.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(4,deleteComponnentCommand1.component->getAllConnections().size());
    //use command to delete relationShip
    DeleteComponentCommand deleteComponnentCommand2 = DeleteComponentCommand(this->componentMap,this->componentMap.get("7"));
    ASSERT_EQ(2,deleteComponnentCommand2.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand2.execute();
    ASSERT_EQ(16,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand2.component->getAllConnections().size());
    deleteComponnentCommand2.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(2,deleteComponnentCommand2.component->getAllConnections().size());
    deleteComponnentCommand2.execute();
    ASSERT_EQ(16,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand2.component->getAllConnections().size());
    deleteComponnentCommand2.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(2,deleteComponnentCommand2.component->getAllConnections().size());
    //use command to delete attribute
    DeleteComponentCommand deleteComponnentCommand3 = DeleteComponentCommand(this->componentMap,this->componentMap.get("10"));
    ASSERT_EQ(1,deleteComponnentCommand3.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand3.execute();
    ASSERT_EQ(17,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand3.component->getAllConnections().size());
    deleteComponnentCommand3.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(1,deleteComponnentCommand3.component->getAllConnections().size());
    deleteComponnentCommand3.execute();
    ASSERT_EQ(17,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand3.component->getAllConnections().size());
    deleteComponnentCommand3.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(1,deleteComponnentCommand3.component->getAllConnections().size());
    //use command to delete connector
    DeleteComponentCommand deleteComponnentCommand4 = DeleteComponentCommand(this->componentMap,this->componentMap.get("16"));
    deleteComponnentCommand4.component = this->componentMap.get("16");
    ASSERT_EQ(2,deleteComponnentCommand4.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand4.execute();
    ASSERT_EQ(18,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand4.component->getAllConnections().size());
    deleteComponnentCommand4.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(2,deleteComponnentCommand4.component->getAllConnections().size());
    deleteComponnentCommand4.execute();
    ASSERT_EQ(18,this->componentMap.size());
    ASSERT_EQ(0,deleteComponnentCommand4.component->getAllConnections().size());
    deleteComponnentCommand4.unExecute();
    ASSERT_EQ(19,this->componentMap.size());
    ASSERT_EQ(2,deleteComponnentCommand4.component->getAllConnections().size());
}

TEST_F(DeleteComponentCommandTest,testSaveConnectionData){
    HashMap<string,Connector*> connectorMap;
    for each(Component* component in this->componentMap){
        Connector* connector = dynamic_cast<Connector*>(component);
        if(!connector)
            continue;
        connectorMap.put(connector->getID(),connector);
    }
    for each(Connector* connector in connectorMap){
        DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(this->componentMap,connector);
        deleteComponnentCommand.saveConnectionData(connector);
        ConnectionData* connectionData = deleteComponnentCommand.connectionDataMap.get(connector->getID());
        ASSERT_EQ(connectionData->getConnectedFirstNodeID(),connector->getFirstConnectedNode()->getID());
        ASSERT_EQ(connectionData->getConnectedSecondNodeID(),connector->getSecondConnectedNode()->getID());
    }
}

TEST_F(DeleteComponentCommandTest,testClearConnectionDataMap){
    DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("0"));
    ASSERT_EQ(0,deleteComponnentCommand.connectionDataMap.size());

    deleteComponnentCommand.execute();
    ASSERT_EQ(4,deleteComponnentCommand.connectionDataMap.size());

    deleteComponnentCommand.clearConnectionDataMap();
    ASSERT_EQ(0,deleteComponnentCommand.connectionDataMap.size());
}

TEST_F(DeleteComponentCommandTest,testRemoveAndDisconnectComponents){
    DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("0"));

    ASSERT_EQ(19,this->componentMap.size());
    deleteComponnentCommand.removeAndDisconnectComponents();
    ASSERT_EQ(14,this->componentMap.size());
}

TEST_F(DeleteComponentCommandTest,testReConnectComponents){
    DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(this->componentMap,this->componentMap.get("0"));

    ConnectionData connectionData = ConnectionData("0","1","4");
    Connector* connector = static_cast<Connector*>(this->componentMap.get("4"));
    ASSERT_EQ(2,connector->getAllConnections().size());
    connector->breakAllConnections();
    ASSERT_EQ(0,connector->getAllConnections().size());

    deleteComponnentCommand.reConnectComponents(&connectionData,connector);
    ASSERT_EQ(2,connector->getAllConnections().size());
}