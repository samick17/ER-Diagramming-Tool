#include "DeleteComponentCommandTest.h"
#include "DeleteComponentCommand.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"

void DeleteComponentCommandTest::SetUp(){
	this->presentation = new Presentation(&this->erModel);
    this->textPresentation = new TextPresentation(this->presentation);
    Component* entity1 = this->erModel.addNode(ComponentType::TypeEntity);
    Component* attribute1 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* attribute2 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* attribute3 = this->erModel.addNode(ComponentType::TypeAttribute);
    this->erModel.addConnection(entity1,attribute1);
    this->erModel.addConnection(entity1,attribute2);
    this->erModel.addConnection(entity1,attribute3);
    Component* relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
    this->erModel.addConnection(entity1,relationShip);
    Component* attribute4 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* attribute5 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* attribute6 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* attribute7 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
    this->erModel.addConnection(entity2,attribute4);
    this->erModel.addConnection(entity2,attribute5);
    this->erModel.addConnection(entity2,attribute6);
    this->erModel.addConnection(entity2,attribute7);
    this->erModel.addConnection(entity2,relationShip);
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
}

void DeleteComponentCommandTest::TearDown(){
	delete this->presentation;
    delete this->textPresentation;
}

TEST_F(DeleteComponentCommandTest,testDeleteComponentCommand){
    //delete entity
    DeleteComponentCommand deleteComponnentCommand1 = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("0"));
    ASSERT_EQ(4,deleteComponnentCommand1.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand1.execute();
    ASSERT_EQ(14,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand1.component->getAllConnections().size());
    deleteComponnentCommand1.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(4,deleteComponnentCommand1.component->getAllConnections().size());
    deleteComponnentCommand1.execute();
    ASSERT_EQ(14,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand1.component->getAllConnections().size());
    deleteComponnentCommand1.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(4,deleteComponnentCommand1.component->getAllConnections().size());
    //use command to delete relationShip
    DeleteComponentCommand deleteComponnentCommand2 = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("7"));
    ASSERT_EQ(2,deleteComponnentCommand2.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand2.execute();
    ASSERT_EQ(16,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand2.component->getAllConnections().size());
    deleteComponnentCommand2.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(2,deleteComponnentCommand2.component->getAllConnections().size());
    deleteComponnentCommand2.execute();
    ASSERT_EQ(16,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand2.component->getAllConnections().size());
    deleteComponnentCommand2.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(2,deleteComponnentCommand2.component->getAllConnections().size());
    //use command to delete attribute
    DeleteComponentCommand deleteComponnentCommand3 = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("10"));
    ASSERT_EQ(1,deleteComponnentCommand3.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand3.execute();
    ASSERT_EQ(17,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand3.component->getAllConnections().size());
    deleteComponnentCommand3.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(1,deleteComponnentCommand3.component->getAllConnections().size());
    deleteComponnentCommand3.execute();
    ASSERT_EQ(17,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand3.component->getAllConnections().size());
    deleteComponnentCommand3.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(1,deleteComponnentCommand3.component->getAllConnections().size());
    //use command to delete connector
    DeleteComponentCommand deleteComponnentCommand4 = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("16"));
    deleteComponnentCommand4.component = this->erModel.getComponentByID("16");
    ASSERT_EQ(2,deleteComponnentCommand4.component->getAllConnections().size());
    //test execute & unexecute
    deleteComponnentCommand4.execute();
    ASSERT_EQ(18,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand4.component->getAllConnections().size());
    deleteComponnentCommand4.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(2,deleteComponnentCommand4.component->getAllConnections().size());
    deleteComponnentCommand4.execute();
    ASSERT_EQ(18,this->erModel.getAllComponents().size());
    ASSERT_EQ(0,deleteComponnentCommand4.component->getAllConnections().size());
    deleteComponnentCommand4.unExecute();
    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    ASSERT_EQ(2,deleteComponnentCommand4.component->getAllConnections().size());
}

TEST_F(DeleteComponentCommandTest,testSaveConnectionData){
    for each(Connector* connector in this->erModel.getAllConnectors()){
        DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(&this->erModel,connector);
        deleteComponnentCommand.saveConnectionData(connector);
        ConnectionData* connectionData = deleteComponnentCommand.connectionDataMap.get(connector->getID());
        ASSERT_EQ(connectionData->getConnectedFirstNodeID(),connector->getFirstConnectedNode()->getID());
        ASSERT_EQ(connectionData->getConnectedSecondNodeID(),connector->getSecondConnectedNode()->getID());
    }
}

TEST_F(DeleteComponentCommandTest,testClearConnectionDataMap){
	DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("0"));
    
	ASSERT_EQ(0,deleteComponnentCommand.connectionDataMap.size());

	deleteComponnentCommand.execute();

    ASSERT_EQ(4,deleteComponnentCommand.connectionDataMap.size());

    deleteComponnentCommand.clearConnectionDataMap();

    ASSERT_EQ(0,deleteComponnentCommand.connectionDataMap.size());
}

TEST_F(DeleteComponentCommandTest,testRemoveAndDisconnectComponents){
    DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("0"));

    ASSERT_EQ(19,this->erModel.getAllComponents().size());
    deleteComponnentCommand.removeAndDisconnectComponents();
    ASSERT_EQ(14,this->erModel.getAllComponents().size());
}

TEST_F(DeleteComponentCommandTest,testReConnectComponents){
    DeleteComponentCommand deleteComponnentCommand = DeleteComponentCommand(&this->erModel,this->erModel.getComponentByID("0"));

    ConnectionData connectionData = ConnectionData("0","1","4");
    Connector* connector = this->erModel.getAllConnectors().get("4");
    ASSERT_EQ(2,connector->getAllConnections().size());
    connector->breakAllConnections();
    ASSERT_EQ(0,connector->getAllConnections().size());

    deleteComponnentCommand.reConnectComponents(&connectionData,connector);
    ASSERT_EQ(2,connector->getAllConnections().size());
}