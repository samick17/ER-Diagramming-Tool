#include "IntegrationTest.h"
#include "DirectoryUtil.h"
#include "Document.h"
#include "FileParser.h"
#include "FileNotFoundException.h"
#include "EmptyCollectionException.h"
#include "NoSuchKeyException.h"
#include "ComponentType.h"
#include "DeleteComponentCommand.h"
#include "ConnectNodeCommand.h"

void IntegrationTest::SetUp(){	
	this->presentation = new Presentation(&erModel);
	this->commandManager = new CommandManager(presentation);
	ASSERT_THROW(this->erModel.getAllComponents(),EmptyCollectionException);
	//set file directory
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/Debug/testdata";
	_mkdir(directory.c_str());
	//save file to directory
	string filePath = directory+"/test_file1.erd";
	Document doc(filePath);	
	string fileData[] = {
		"E, Engineer","A, Emp_ID","R, Has","A, Name","E, PC","A, PC_ID","A, Purchase_Date","C","C","C","C","C, 1","C, 1","A, Department","C",
		"",
		"7 0,1","8 0,3","9 4,5","10 4,6","11 0,2","12 2,4","14 0,13",
		"",
		"0 1,3","4 5"
	};
	for (int lineIndex = 0;lineIndex<sizeof(fileData)/sizeof(*fileData);lineIndex++)
		doc.wirteLine(fileData[lineIndex]);
	doc.saveFile();
	//load file to model
	FileParser fileParser;
	fileParser.parseFileToModel(filePath,&this->erModel);
	//Assert Diagram is loaded correctly
	assertLoadFileCorrectly();
}

void IntegrationTest::TearDown(){	
	//delete file
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/Debug/testdata";
	string filePath = directory+"/test_file1.erd";	
	remove(filePath.c_str());
	_rmdir(directory.c_str());
	//delete pointer
	delete this->presentation;
	delete this->commandManager;
}
//Assert Diagram is loaded correctly
void IntegrationTest::assertLoadFileCorrectly(){
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

TEST_F(IntegrationTest,testLoadFileNotExist){
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	string filePath = directory+"/file_not_exist.erd";
	FileParser fileParser;
	ASSERT_THROW(fileParser.parseFileToModel(filePath,&this->erModel),FileNotFoundException);
}

TEST_F(IntegrationTest,testIsPrimaryExist){
	//Assert Table
	HashMap<string,Table*> tableMap = this->erModel.getAllTables();
	Attribute* attributeEmp_ID = static_cast<Attribute*>(this->erModel.componentMap.get("1"));
	Attribute* attributeName = static_cast<Attribute*>(this->erModel.componentMap.get("3"));
	Attribute* attributePC_ID = static_cast<Attribute*>(this->erModel.componentMap.get("5"));
	Attribute* attributePurchase_Date = static_cast<Attribute*>(this->erModel.componentMap.get("6"));
	Attribute* attributeDepartment = static_cast<Attribute*>(this->erModel.componentMap.get("13"));

	ASSERT_EQ(2,tableMap.size());
	ASSERT_EQ(true,tableMap.containsKey("0"));
	ASSERT_EQ(true,tableMap.containsKey("4"));
	Table* tableEngineer = tableMap.get("0");
	Table* tablePC = tableMap.get("4");

	ASSERT_EQ(3,tableEngineer->attributeMap.size());
	ASSERT_EQ(0,tableEngineer->foreignKeyAttributeMap.size());
	ASSERT_EQ(true,tableEngineer->attributeMap.containsKey(attributeEmp_ID->getID()));
	ASSERT_EQ(true,tableEngineer->attributeMap.containsKey(attributeName->getID()));
	ASSERT_EQ(true,tableEngineer->attributeMap.containsKey(attributeDepartment->getID()));

	ASSERT_EQ(2,tablePC->attributeMap.size());	
	ASSERT_EQ(2,tablePC->foreignKeyAttributeMap.size());
	ASSERT_EQ(true,tablePC->attributeMap.containsKey(attributePC_ID->getID()));
	ASSERT_EQ(true,tablePC->attributeMap.containsKey(attributePurchase_Date->getID()));		

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

	DeleteComponentCommand* deleteComponentCommand = new DeleteComponentCommand(this->presentation);
	deleteComponentCommand->component = entityTest;	
	this->commandManager->execute(deleteComponentCommand);
		
	ASSERT_THROW(this->erModel.componentMap.get(entityTest->getID()),NoSuchKeyException);
	ASSERT_EQ(15,this->erModel.componentMap.size());

	this->commandManager->undo();

	ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
	ASSERT_EQ(16,this->erModel.componentMap.size());
}

TEST_F(IntegrationTest,testRedoConnectComponent){
	Entity* entityTest = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
	entityTest->setName("Test");

	ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
	ASSERT_EQ(16,this->erModel.componentMap.size());

	Attribute* attributeTest_Attr = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
	attributeTest_Attr->setName("Test Attr");

	ASSERT_EQ(attributeTest_Attr,this->erModel.componentMap.get(attributeTest_Attr->getID()));
	ASSERT_EQ(17,this->erModel.componentMap.size());

	ConnectNodeCommand* connectNodeCommand = new ConnectNodeCommand(this->presentation);
	connectNodeCommand->firstNode = entityTest;
	connectNodeCommand->secondNode = attributeTest_Attr;
	this->commandManager->execute(connectNodeCommand);
	
	Connector* connector = static_cast<Connector*>(this->erModel.getComponentByID("17"));
	ASSERT_EQ(true,connector->isNodesConnection(entityTest,attributeTest_Attr));
	ASSERT_EQ(18,this->erModel.componentMap.size());

	this->commandManager->undo();
	ASSERT_EQ(false,connector->isNodesConnection(entityTest,attributeTest_Attr));
	ASSERT_EQ(17,this->erModel.componentMap.size());

	this->commandManager->redo();
	ASSERT_EQ(true,connector->isNodesConnection(entityTest,attributeTest_Attr));
	ASSERT_EQ(18,this->erModel.componentMap.size());
}

TEST_F(IntegrationTest,testCommonUsage){

}