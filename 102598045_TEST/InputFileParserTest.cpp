#include "InputFileParserTest.h"
#include "StringSymbol.h"
#include "ComponentType.h"

void InputFileParserTest::SetUp(){
    this->inputFileParser.erModel = &erModel;
    this->document = new Document("TestDoc");
    document->writeLine("E, Engineer");
    document->writeLine("A, Emp_ID");
    document->writeLine("R, Has");
    document->writeLine("A, Name");
    document->writeLine("E, PC");
    document->writeLine("A, PC_ID");
    document->writeLine("A, Purchase_Date");
    document->writeLine("C");
    document->writeLine("C");
    document->writeLine("C");
    document->writeLine("C");
    document->writeLine("C, 1");
    document->writeLine("C, 1");
    document->writeLine("A, Department");
    document->writeLine("C");
    document->writeLine("");
    document->writeLine("7 0,1");
    document->writeLine("8 0,3");
    document->writeLine("9 4,5");
    document->writeLine("10 4,6");
    document->writeLine("11 0,2");
    document->writeLine("12 2,4");
    document->writeLine("14 0,13");
    document->writeLine("");
    document->writeLine("0 1,3");
    document->writeLine("4 5");
    document->writeLine("");
    ASSERT_EQ(true,this->inputFileParser.componentDataQueue.empty());
    ASSERT_EQ(true,this->inputFileParser.connectionDataQueue.empty());
}

void InputFileParserTest::TearDown(){
    delete this->document;
}

TEST_F(InputFileParserTest,testLoadAllComponentsFromDoc){
    ASSERT_EQ(true,this->inputFileParser.componentDataQueue.empty());
    this->inputFileParser.loadAllComponentsFromDoc(*this->document);
    ASSERT_EQ(15,this->inputFileParser.componentDataQueue.size());
}

TEST_F(InputFileParserTest,testLoadAllConnectorsFromDoc){
    this->document->readIndex = 16;
    ASSERT_EQ(true,this->inputFileParser.connectionDataQueue.empty());
    this->inputFileParser.loadAllConnectorsFromDoc(*this->document);
    ASSERT_EQ(7,this->inputFileParser.connectionDataQueue.size());
}

TEST_F(InputFileParserTest,testLoadAllPrimaryKeyAndSetUpFromDoc){    
    this->inputFileParser.loadAllComponentsFromDoc(*this->document);
    this->inputFileParser.loadAllConnectorsFromDoc(*this->document);
    this->inputFileParser.addAllComponentToERModel();
    Entity* entityEngineer = static_cast<Entity*>(this->erModel.getComponentByID("0"));
    Entity* entityPC = static_cast<Entity*>(this->erModel.getComponentByID("4"));
    ASSERT_EQ(0,entityEngineer->getPrimaryKeyAttributes().size());
    ASSERT_EQ(0,entityPC->getPrimaryKeyAttributes().size());
    //load all Primary Key
    this->inputFileParser.loadAllPrimaryKeyAndSetUpFromDoc(*this->document);
    ASSERT_EQ(2,entityEngineer->getPrimaryKeyAttributes().size());
    ASSERT_EQ(true,entityEngineer->getPrimaryKeyAttributes().get("1")->isPrimaryKey());
    ASSERT_EQ(true,entityEngineer->getPrimaryKeyAttributes().get("3")->isPrimaryKey());
    ASSERT_EQ(1,entityPC->getPrimaryKeyAttributes().size());
    ASSERT_EQ(true,entityPC->getPrimaryKeyAttributes().get("5")->isPrimaryKey());
}

TEST_F(InputFileParserTest,testAddAllComponentToERModel){
    queue<StringPair> componentDataQueue;
    queue<ConnectionData> connectionDataQueue;

    componentDataQueue.push(StringPair(ComponentType::TypeAttribute,"Name"));
    componentDataQueue.push(StringPair(ComponentType::TypeEntity,"Character"));
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//2 0 1
    componentDataQueue.push(StringPair(ComponentType::TypeAttribute,"ID"));
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//4 1 3
    componentDataQueue.push(StringPair(ComponentType::TypeAttribute,"Age"));
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//6 1 5
    componentDataQueue.push(StringPair(ComponentType::TypeRelationShip,"Has"));
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//8 1 7
    componentDataQueue.push(StringPair(ComponentType::TypeEntity,"Item"));
    componentDataQueue.push(StringPair(ComponentType::TypeAttribute,"Type"));
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//11 9 10
    componentDataQueue.push(StringPair(ComponentType::TypeAttribute,"Item_ID"));
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//13 9 12
    componentDataQueue.push(StringPair(ComponentType::TypeConnector,""));//14 7 9

    connectionDataQueue.push(ConnectionData("2","0","1"));
    connectionDataQueue.push(ConnectionData("4","1","3"));
    connectionDataQueue.push(ConnectionData("6","1","5"));
    connectionDataQueue.push(ConnectionData("8","1","7"));
    connectionDataQueue.push(ConnectionData("11","9","10"));
    connectionDataQueue.push(ConnectionData("13","9","12"));
    connectionDataQueue.push(ConnectionData("14","7","9"));

    this->inputFileParser.componentDataQueue = componentDataQueue;
    this->inputFileParser.connectionDataQueue = connectionDataQueue;

    this->inputFileParser.addAllComponentToERModel();
    ASSERT_EQ(15,this->erModel.getAllComponents().size());
    ASSERT_EQ(2,this->erModel.getAllEntities().size());
    ASSERT_EQ(1,this->erModel.getAllRelationShips().size());
    ASSERT_EQ(7,this->erModel.getAllConnectors().size());

    ASSERT_EQ(3,this->erModel.getAllEntities().get("1")->getConnectedAttributes().size());
    ASSERT_EQ(2,this->erModel.getAllEntities().get("9")->getConnectedAttributes().size());
    //assert all components
    //assert name
    ASSERT_EQ("Name",this->erModel.getComponentByID("0")->getName());
    ASSERT_EQ("Character",this->erModel.getComponentByID("1")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("2")->getName());
    ASSERT_EQ("ID",this->erModel.getComponentByID("3")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("4")->getName());
    ASSERT_EQ("Age",this->erModel.getComponentByID("5")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("6")->getName());
    ASSERT_EQ("Has",this->erModel.getComponentByID("7")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("8")->getName());
    ASSERT_EQ("Item",this->erModel.getComponentByID("9")->getName());
    ASSERT_EQ("Type",this->erModel.getComponentByID("10")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("11")->getName());
    ASSERT_EQ("Item_ID",this->erModel.getComponentByID("12")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("13")->getName());
    ASSERT_EQ("",this->erModel.getComponentByID("14")->getName());
    //assert id
    ASSERT_EQ("0",this->erModel.getComponentByID("0")->getID());
    ASSERT_EQ("1",this->erModel.getComponentByID("1")->getID());
    ASSERT_EQ("2",this->erModel.getComponentByID("2")->getID());
    ASSERT_EQ("3",this->erModel.getComponentByID("3")->getID());
    ASSERT_EQ("4",this->erModel.getComponentByID("4")->getID());
    ASSERT_EQ("5",this->erModel.getComponentByID("5")->getID());
    ASSERT_EQ("6",this->erModel.getComponentByID("6")->getID());
    ASSERT_EQ("7",this->erModel.getComponentByID("7")->getID());
    ASSERT_EQ("8",this->erModel.getComponentByID("8")->getID());
    ASSERT_EQ("9",this->erModel.getComponentByID("9")->getID());
    ASSERT_EQ("10",this->erModel.getComponentByID("10")->getID());
    ASSERT_EQ("11",this->erModel.getComponentByID("11")->getID());
    ASSERT_EQ("12",this->erModel.getComponentByID("12")->getID());
    ASSERT_EQ("13",this->erModel.getComponentByID("13")->getID());
    ASSERT_EQ("14",this->erModel.getComponentByID("14")->getID());
}

TEST_F(InputFileParserTest,testAddConnector){
    Component* attribute1 = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* relatuonShip = this->erModel.addNode(ComponentType::TypeRelationShip);
    Component* entity = this->erModel.addNode(ComponentType::TypeEntity);
    this->inputFileParser.addConnector(ConnectionData("3","0","2"),"1");
    Component* connector1 = this->erModel.getComponentByID("3");
    ASSERT_EQ(1,attribute1->getAllConnections().size());
    ASSERT_EQ(1,entity->getAllConnections().size());
    ASSERT_EQ(2,connector1->getAllConnections().size());
    ASSERT_EQ(true,attribute1->hasConnectedTo(entity));
    ASSERT_EQ(true,entity->hasConnectedTo(attribute1));
    this->inputFileParser.addConnector(ConnectionData("4","2","1"),"N");
    Component* connector2 = this->erModel.getComponentByID("4");
    ASSERT_EQ(2,entity->getAllConnections().size());
    ASSERT_EQ(1,relatuonShip->getAllConnections().size());
    ASSERT_EQ(2,connector2->getAllConnections().size());
    ASSERT_EQ(true,entity->hasConnectedTo(relatuonShip));
    ASSERT_EQ(true,relatuonShip->hasConnectedTo(entity));
    Component* attribute2 = this->erModel.addNode(ComponentType::TypeAttribute);
    this->inputFileParser.addConnector(ConnectionData("6","5","2"),"");
    Component* connector3 = this->erModel.getComponentByID("6");
    ASSERT_EQ(1,attribute2->getAllConnections().size());
    ASSERT_EQ(3,entity->getAllConnections().size());
    ASSERT_EQ(2,connector3->getAllConnections().size());
    ASSERT_EQ(true,attribute2->hasConnectedTo(entity));
    ASSERT_EQ(true,entity->hasConnectedTo(attribute2));
}

TEST_F(InputFileParserTest,testIsQueueArriveConnectionDataID){
    ASSERT_EQ(false,this->inputFileParser.isQueueArriveConnectionDataID(0));

    this->inputFileParser.componentDataQueue.push(StringPair(ComponentType::TypeAttribute,"Name"));
    ASSERT_EQ(false,this->inputFileParser.isQueueArriveConnectionDataID(10));
    this->inputFileParser.connectionDataQueue.push(ConnectionData("5","0","1"));
    ASSERT_EQ(true,this->inputFileParser.isQueueArriveConnectionDataID(5));
    //assert fail
    ASSERT_EQ(false,this->inputFileParser.isQueueArriveConnectionDataID(18));
}