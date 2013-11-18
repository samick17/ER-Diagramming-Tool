#include "IntegrationTest.h"
#include "DirectoryUtil.h"
#include "Document.h"
#include "InputFileParser.h"
#include "FileNotFoundException.h"
#include "EmptyCollectionException.h"
#include "NoSuchNodeException.h"
#include "NoSuchKeyException.h"
#include "NullPointerException.h"
#include "ComponentType.h"
#include "TextUIPresenter.h"
#include "FileCreator.h"

void IntegrationTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->textPresentation = new TextPresentation(this->presentation);
    this->textUIPresenter = new TextUIPresenter(this->textPresentation);
    ASSERT_EQ(0,this->erModel.getAllComponents().size());

    //create file & load file to model
    string filePath = FileCreator::createDefaultFile();
    InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(filePath,&this->erModel);
    //Assert Diagram is loaded correctly
    ASSERT_EQ(15,this->erModel.componentMap.size());
    //Assert all component type is correct
    ASSERT_EQ(ComponentType::TypeEntity,this->erModel.componentMap.get("0")->getType());
    ASSERT_EQ(ComponentType::TypeAttribute,this->erModel.componentMap.get("1")->getType());
    ASSERT_EQ(ComponentType::TypeRelationShip,this->erModel.componentMap.get("2")->getType());
    ASSERT_EQ(ComponentType::TypeAttribute,this->erModel.componentMap.get("3")->getType());
    ASSERT_EQ(ComponentType::TypeEntity,this->erModel.componentMap.get("4")->getType());
    ASSERT_EQ(ComponentType::TypeAttribute,this->erModel.componentMap.get("5")->getType());
    ASSERT_EQ(ComponentType::TypeAttribute,this->erModel.componentMap.get("6")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("7")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("8")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("9")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("10")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("11")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("12")->getType());
    ASSERT_EQ(ComponentType::TypeAttribute,this->erModel.componentMap.get("13")->getType());
    ASSERT_EQ(ComponentType::TypeConnector,this->erModel.componentMap.get("14")->getType());
    //Assert all component name is correct
    ASSERT_EQ("Engineer",this->erModel.componentMap.get("0")->getName());
    ASSERT_EQ("Emp_ID",this->erModel.componentMap.get("1")->getName());
    ASSERT_EQ("Has",this->erModel.componentMap.get("2")->getName());
    ASSERT_EQ("Name",this->erModel.componentMap.get("3")->getName());
    ASSERT_EQ("PC",this->erModel.componentMap.get("4")->getName());
    ASSERT_EQ("PC_ID",this->erModel.componentMap.get("5")->getName());
    ASSERT_EQ("Purchase_Date",this->erModel.componentMap.get("6")->getName());
    ASSERT_EQ("",this->erModel.componentMap.get("7")->getName());
    ASSERT_EQ("",this->erModel.componentMap.get("8")->getName());
    ASSERT_EQ("",this->erModel.componentMap.get("9")->getName());
    ASSERT_EQ("",this->erModel.componentMap.get("10")->getName());
    ASSERT_EQ(RelationType::OneToOne,this->erModel.componentMap.get("11")->getName());
    ASSERT_EQ(RelationType::OneToOne,this->erModel.componentMap.get("12")->getName());
    ASSERT_EQ("Department",this->erModel.componentMap.get("13")->getName());
    ASSERT_EQ("",this->erModel.componentMap.get("14")->getName());
    //Assert all component's connections is correct
    ASSERT_EQ(4,this->erModel.componentMap.get("0")->getAllConnections().size());
    ASSERT_EQ(1,this->erModel.componentMap.get("1")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("2")->getAllConnections().size());
    ASSERT_EQ(1,this->erModel.componentMap.get("3")->getAllConnections().size());
    ASSERT_EQ(3,this->erModel.componentMap.get("4")->getAllConnections().size());
    ASSERT_EQ(1,this->erModel.componentMap.get("5")->getAllConnections().size());
    ASSERT_EQ(1,this->erModel.componentMap.get("6")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("7")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("8")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("9")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("10")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("11")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("12")->getAllConnections().size());
    ASSERT_EQ(1,this->erModel.componentMap.get("13")->getAllConnections().size());
    ASSERT_EQ(2,this->erModel.componentMap.get("14")->getAllConnections().size());
}

void IntegrationTest::TearDown(){
    //delete file
    FileCreator::deleteDefaultFile();
    //delete pointer
    delete this->presentation;
    delete this->textPresentation;
}

TEST_F(IntegrationTest,testLoadFileNotExist){
    string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
    string filePath = directory+"/file_not_exist.erd";
    InputFileParser inputFileParser;
    ASSERT_THROW(inputFileParser.parseFileToModel(filePath,&this->erModel),FileNotFoundException);
}

TEST_F(IntegrationTest,testIsPrimaryExist){
    //Display Table
    this->textUIPresenter->displayTable();

    Attribute* attributeEmp_ID = static_cast<Attribute*>(this->erModel.componentMap.get("1"));
    Attribute* attributeName = static_cast<Attribute*>(this->erModel.componentMap.get("3"));
    Attribute* attributePC_ID = static_cast<Attribute*>(this->erModel.componentMap.get("5"));
    Attribute* attributePurchase_Date = static_cast<Attribute*>(this->erModel.componentMap.get("6"));
    Attribute* attributeDepartment = static_cast<Attribute*>(this->erModel.componentMap.get("13"));
        
    //Assert primary key
    ASSERT_EQ(true,attributeEmp_ID->isPrimaryKey());
    ASSERT_EQ(true,attributeName->isPrimaryKey());
    ASSERT_EQ(true,attributePC_ID->isPrimaryKey());
    ASSERT_EQ(false,attributePurchase_Date->isPrimaryKey());
    ASSERT_EQ(false,attributeDepartment->isPrimaryKey());
    //Assert Entity: Engineer's primary key is "Name" & "Emp_ID"
    Entity* entityEngineer = static_cast<Entity*>(this->erModel.componentMap.get("0"));
    ASSERT_EQ(3,entityEngineer->getConnectedAttributes().size());
    ASSERT_EQ(2,entityEngineer->getPrimaryKeyAttributes().size());
    ASSERT_EQ(true,entityEngineer->getConnectedAttributes().containsKey(attributeEmp_ID->getID()));
    ASSERT_EQ(true,entityEngineer->getConnectedAttributes().containsKey(attributeName->getID()));
    ASSERT_EQ(true,entityEngineer->getConnectedAttributes().containsKey(attributeDepartment->getID()));
    ASSERT_EQ(true,entityEngineer->getPrimaryKeyAttributes().containsKey(attributeEmp_ID->getID()));
    ASSERT_EQ(true,entityEngineer->getPrimaryKeyAttributes().containsKey(attributeName->getID()));
    
    ASSERT_EQ(attributeEmp_ID,entityEngineer->getConnectedAttributes().get(attributeEmp_ID->getID()));
    ASSERT_EQ(attributeName,entityEngineer->getConnectedAttributes().get(attributeName->getID()));
    ASSERT_EQ(attributeDepartment,entityEngineer->getConnectedAttributes().get(attributeDepartment->getID()));
    ASSERT_EQ(attributeEmp_ID,entityEngineer->getPrimaryKeyAttributes().get(attributeEmp_ID->getID()));
    ASSERT_EQ(attributeName,entityEngineer->getPrimaryKeyAttributes().get(attributeName->getID()));
    //Assert Entity: PC's primary key is "PC_ID"
    Entity* entityPC = static_cast<Entity*>(this->erModel.componentMap.get("4"));
    ASSERT_EQ(2,entityPC->getConnectedAttributes().size());
    ASSERT_EQ(1,entityPC->getPrimaryKeyAttributes().size());
    ASSERT_EQ(true,entityPC->getConnectedAttributes().containsKey(attributePC_ID->getID()));
    ASSERT_EQ(true,entityPC->getConnectedAttributes().containsKey(attributePurchase_Date->getID()));
    ASSERT_EQ(true,entityPC->getPrimaryKeyAttributes().containsKey(attributePC_ID->getID()));

    ASSERT_EQ(attributePC_ID,entityPC->getConnectedAttributes().get(attributePC_ID->getID()));
    ASSERT_EQ(attributePurchase_Date,entityPC->getConnectedAttributes().get(attributePurchase_Date->getID()));
    ASSERT_EQ(attributePC_ID,entityPC->getConnectedAttributes().get(attributePC_ID->getID()));
    //Assert PC's primary key is not "Purchase_Date"
    ASSERT_EQ(false,entityPC->getPrimaryKeyAttributes().containsKey(attributePurchase_Date->getID()));
}

TEST_F(IntegrationTest,testUndoDeleteComponent){
    Entity* entityTest = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    entityTest->setName("Test");

    ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
    ASSERT_EQ(16,this->erModel.componentMap.size());

    this->erModel.deleteComponent(entityTest);
        
    ASSERT_THROW(this->erModel.componentMap.get(entityTest->getID()),NoSuchKeyException);
    ASSERT_EQ(15,this->erModel.componentMap.size());

    this->erModel.undo();

    ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
    ASSERT_EQ(16,this->erModel.componentMap.size());
}

TEST_F(IntegrationTest,testRedoConnectComponent){
    Entity* entityTest = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    entityTest->setName("Test");

    ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
    ASSERT_EQ(16,this->erModel.componentMap.size());

    Attribute* attributeTestAttr = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    attributeTestAttr->setName("Test Attr");

    ASSERT_EQ(attributeTestAttr,this->erModel.componentMap.get(attributeTestAttr->getID()));
    ASSERT_EQ(17,this->erModel.componentMap.size());

    this->erModel.addConnection(entityTest,attributeTestAttr);

    Connector* connector = static_cast<Connector*>(this->erModel.getComponentByID("17"));
    ASSERT_EQ(true,connector->isNodesConnection(entityTest,attributeTestAttr));
    ASSERT_EQ(18,this->erModel.componentMap.size());

    this->erModel.undo();
    ASSERT_EQ(false,connector->isNodesConnection(entityTest,attributeTestAttr));
    ASSERT_EQ(17,this->erModel.componentMap.size());

    this->erModel.redo();
    ASSERT_EQ(true,connector->isNodesConnection(entityTest,attributeTestAttr));
    ASSERT_EQ(18,this->erModel.componentMap.size());
}

TEST_F(IntegrationTest,testCommonUsage){
    //Add entity "Work Diary" & set name as "Work Diary" , ASSERT
    Entity* entityWorkDiary = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    entityWorkDiary->setName("Work Diary");
    ASSERT_EQ(entityWorkDiary,this->erModel.componentMap.get(entityWorkDiary->getID()));
    ASSERT_EQ("Work Diary",this->erModel.componentMap.get(entityWorkDiary->getID())->getName());
    ASSERT_EQ(16,this->erModel.componentMap.size());
    //Add relationShip "Write" & set name as "Write" , ASSERT
    Component* relationShipWrite = this->erModel.addNode(ComponentType::TypeRelationShip);
    relationShipWrite->setName("Write");
    ASSERT_EQ(relationShipWrite,this->erModel.componentMap.get(relationShipWrite->getID()));
    ASSERT_EQ("Write",this->erModel.componentMap.get(relationShipWrite->getID())->getName());
    ASSERT_EQ(17,this->erModel.componentMap.size());
    //connect node0 & node16
    Component* node0 = this->erModel.componentMap.get("0");
    Component* node16 = this->erModel.componentMap.get("16");
    this->erModel.addConnection(node0,node16);
    //set cardinality as 1
    Connector* connectorNode0AndNode6 = this->erModel.getNodesConnector(node0,node16);
    ASSERT_EQ(18,this->erModel.componentMap.size());
    connectorNode0AndNode6->setName(RelationType::OneToOne);
    //ASSERT 0 & 16 has connected    
    ASSERT_EQ(true,node0->hasConnectedTo(node16));
    ASSERT_EQ(true,node16->hasConnectedTo(node0));
    //connect node15 & node16
    Component* node15 = this->erModel.componentMap.get("15");
    this->erModel.addConnection(node15,node16);
    //ASSERT 15 & 16 has connected
    ASSERT_EQ(19,this->erModel.componentMap.size());
    ASSERT_EQ(true,node15->hasConnectedTo(node16));
    ASSERT_EQ(true,node16->hasConnectedTo(node15));
    //Add attribute "Content" & set name as "Content" , ASSERT
    Component* attributeContent = this->erModel.addNode(ComponentType::TypeAttribute);
    ASSERT_EQ(20,this->erModel.componentMap.size());
    attributeContent->setName("Content");
    ASSERT_EQ(attributeContent,this->erModel.componentMap.get(attributeContent->getID()));
    ASSERT_EQ("Content",this->erModel.componentMap.get(attributeContent->getID())->getName());

    //Add attribute "WD_ID" & set name as "WD_ID" , ASSERT
    Component* attributeWD_ID = this->erModel.addNode(ComponentType::TypeAttribute);
    ASSERT_EQ(21,this->erModel.componentMap.size());
    attributeWD_ID->setName("WD_ID");
    ASSERT_EQ(attributeWD_ID,this->erModel.componentMap.get(attributeWD_ID->getID()));
    ASSERT_EQ("WD_ID",this->erModel.componentMap.get(attributeWD_ID->getID())->getName());
    //Add attribute "WD_date" & set name as "WD_date" , ASSERT
    Component* attributeWD_date = this->erModel.addNode(ComponentType::TypeAttribute);
    ASSERT_EQ(22,this->erModel.componentMap.size());
    attributeWD_date->setName("WD_date");
    ASSERT_EQ(attributeWD_date,this->erModel.componentMap.get(attributeWD_date->getID()));
    ASSERT_EQ("WD_date",this->erModel.componentMap.get(attributeWD_date->getID())->getName());
    //connect node15 & node19 , ASSERT
    Component* node19 = this->erModel.componentMap.get("19");
    this->erModel.addConnection(node15,node19);
    ASSERT_EQ(23,this->erModel.componentMap.size());
    ASSERT_EQ(true,node15->hasConnectedTo(node19));
    ASSERT_EQ(true,node19->hasConnectedTo(node15));
    //connect node15 & node20 , ASSERT
    Component* node20 = this->erModel.componentMap.get("20");
    this->erModel.addConnection(node15,node20);
    ASSERT_EQ(24,this->erModel.componentMap.size());
    ASSERT_EQ(true,node15->hasConnectedTo(node20));
    ASSERT_EQ(true,node20->hasConnectedTo(node15));
    ////connect node15 & node21 , ASSERT
    Component* node21 = this->erModel.componentMap.get("21");
    this->erModel.addConnection(node15,node21);
    ASSERT_EQ(25,this->erModel.componentMap.size());
    ASSERT_EQ(true,node15->hasConnectedTo(node21));
    ASSERT_EQ(true,node21->hasConnectedTo(node15));
    //Set Work Diary primary key "WD_ID" , ASSERT
    vector<string> workdiaryPrimaryKey;
    workdiaryPrimaryKey.push_back(attributeWD_ID->getID());
    entityWorkDiary->setPrimaryKey(workdiaryPrimaryKey);
    ASSERT_EQ(1,entityWorkDiary->getPrimaryKeyAttributes().size());
    ASSERT_EQ(attributeWD_ID,entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID()));
    ASSERT_EQ("WD_ID",entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID())->getName());
    //Display Table
    this->textUIPresenter->displayTable();
    //Assert "Work Diary" exists
    ASSERT_EQ(entityWorkDiary,this->erModel.getComponentByID(entityWorkDiary->getID()));
    //Assert "Work Diary" primary key is "WD_ID"
    ASSERT_EQ(attributeWD_ID,entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID()));
    ASSERT_EQ("WD_ID",entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID())->getName());

    this->erModel.deleteComponent(entityWorkDiary);

    //Assert there is no such node "Work Diary"
    ASSERT_THROW(this->erModel.getComponentByID(entityWorkDiary->getID()),NoSuchNodeException);
    //ASSERT there is no connection between node 15 and 16
    ASSERT_THROW(this->erModel.getNodesConnector(entityWorkDiary,node16),NullPointerException);
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node16));
    ASSERT_EQ(false,node16->hasConnectedTo(entityWorkDiary));
    //ASSERT there is no connection between node 15 and 19
    ASSERT_THROW(this->erModel.getNodesConnector(entityWorkDiary,node19),NullPointerException);
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node19));
    ASSERT_EQ(false,node19->hasConnectedTo(entityWorkDiary));
    //ASSERT there is no connection between node 15 and 20
    ASSERT_THROW(this->erModel.getNodesConnector(entityWorkDiary,node20),NullPointerException);
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node20));
    ASSERT_EQ(false,node20->hasConnectedTo(entityWorkDiary));
    //ASSERT there is no connection between node 15 and 21
    ASSERT_THROW(this->erModel.getNodesConnector(entityWorkDiary,node21),NullPointerException);
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node21));
    ASSERT_EQ(false,node21->hasConnectedTo(entityWorkDiary));
    //Display Table
    this->textUIPresenter->displayTable();    
    //Assert there is no such node "Work Diary"
    ASSERT_THROW(this->erModel.getComponentByID(entityWorkDiary->getID()),NoSuchNodeException);
    //Assert Engineer's primary key is "Name" and "Emp_ID"
    Entity* entityEngineer = static_cast<Entity*>(this->erModel.getComponentByID("0"));
    ASSERT_EQ(this->erModel.getComponentByID("1"),entityEngineer->getPrimaryKeyAttributes().get("1"));
    ASSERT_EQ(this->erModel.getComponentByID("3"),entityEngineer->getPrimaryKeyAttributes().get("3"));
    //Undo
    this->erModel.undo();
    //Display Table
    this->textUIPresenter->displayTable();
    //Assert "Work Diary" primary key is "WD_ID"
    ASSERT_EQ(attributeWD_ID,entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID()));
    ASSERT_EQ("WD_ID",entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID())->getName());
    //Redo
    this->erModel.redo();
    //Assert there is no such node "Work Diary"
    ASSERT_THROW(this->erModel.getComponentByID(entityWorkDiary->getID()),NoSuchNodeException);
    //Assert Engineer's primary key is "Name" and "Emp_ID"    
    ASSERT_EQ(this->erModel.getComponentByID("1"),entityEngineer->getPrimaryKeyAttributes().get("1"));
    ASSERT_EQ(this->erModel.getComponentByID("3"),entityEngineer->getPrimaryKeyAttributes().get("3"));
}