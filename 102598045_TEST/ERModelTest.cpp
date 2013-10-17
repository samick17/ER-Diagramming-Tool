#include "ERModelTest.h"
#include "DirectoryUtil.h"
#include "InvalidNodeTypeException.h"
#include "NullPointerException.h"
#include "NoSuchNodeException.h"
#include "HasConnectedException.h"
#include "InvalidConnectException.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"
#include "FileParser.h"

void ERModelTest::SetUp(){
	ASSERT_EQ(0,this->erModel.componentMap.size());
	//set file directory
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	_mkdir(directory.c_str());
	//save file to directory
	string filePath = directory+"/test_file1.erd";
	Document doc(filePath);	
	string fileData[] = {
		"E, Engineer","A, Emp_ID","R, Has","A, Name","E, PC","A, PC_ID","A, Purchase_Date","C","C","C","C","C, 1","C, 1","A, Department","C",
		"","7 0,1","8 0,3","9 4,5","10 4,6","11 0,2","12 2,4","14 0,13",
		"","0 1,3","4 5"
	};
	for (int lineIndex = 0;lineIndex<sizeof(fileData)/sizeof(*fileData);lineIndex++)
		doc.wirteLine(fileData[lineIndex]);
	doc.saveFile();
	//load file to model
	FileParser fileParser;
	fileParser.parseFileToModel(filePath,&this->erModel);

	ASSERT_EQ(15,this->erModel.componentMap.size());
}

void ERModelTest::TearDown(){	
	//delete file
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	string filePath = directory+"/test_file1.erd";
	remove(filePath.c_str());
	_rmdir(directory.c_str());	
}
//return firstComponent has connection to secondComponent & secondComponent has connection to firstComponent
bool ERModelTest::hasConnected(Component* firstComponent,Component* secondComponent){
	bool isFirstComponentConnectToSecond = false;
	bool isSecondComponentConnectToFirst = false;

	for each(Component* connector in firstComponent->connectionSet){
		if(connector->connectionSet.find(secondComponent) != connector->connectionSet.end())
			isFirstComponentConnectToSecond = true;
	}

	for each(Component* connector in secondComponent->connectionSet){
		if(connector->connectionSet.find(firstComponent) != connector->connectionSet.end())
			isSecondComponentConnectToFirst = true;
	}

	return isFirstComponentConnectToSecond & isSecondComponentConnectToFirst;
}

TEST_F(ERModelTest,testAddNode){
	//test add unknown
	ASSERT_THROW(this->erModel.addNode("X"),InvalidNodeTypeException);	
	ASSERT_THROW(this->erModel.addNode("Q"),InvalidNodeTypeException);
	ASSERT_EQ(15,this->erModel.componentMap.size());
	//test add attribute
	Component* nodeToAdd = this->erModel.addNode(ComponentType::TypeAttribute);
	ASSERT_EQ(ComponentType::TypeAttribute,nodeToAdd->getType());
	ASSERT_EQ(16,this->erModel.componentMap.size());
	//test add entity
	nodeToAdd = this->erModel.addNode(ComponentType::TypeEntity);
	ASSERT_EQ(ComponentType::TypeEntity,nodeToAdd->getType());
	ASSERT_EQ(17,this->erModel.componentMap.size());
	//test add relationsShip
	nodeToAdd = this->erModel.addNode(ComponentType::TypeRelationShip);
	ASSERT_EQ(ComponentType::TypeRelationShip,nodeToAdd->getType());
	ASSERT_EQ(18,this->erModel.componentMap.size());
	//test add connector
	nodeToAdd = this->erModel.addNode(ComponentType::TypeConnector);
	ASSERT_EQ(ComponentType::TypeConnector,nodeToAdd->getType());
	ASSERT_EQ(19,this->erModel.componentMap.size());
}

TEST_F(ERModelTest,testInsertComponent){
	//insert null
	ASSERT_THROW(this->erModel.insertComponent(NULL),NullPointerException);

	Component* attribute = new Attribute(ComponentData("15","Age"));
	this->erModel.insertComponent(attribute);
	ASSERT_EQ(16,this->erModel.componentMap.size());
	//insert again~
	this->erModel.insertComponent(attribute);
	ASSERT_EQ(16,this->erModel.componentMap.size());

	Component* entity = new Entity(ComponentData("16","NoteBook"));
	this->erModel.insertComponent(entity);
	ASSERT_EQ(17,this->erModel.componentMap.size());

	Component* relationShip = new RelationShip(ComponentData("17","Work on"));
	this->erModel.insertComponent(relationShip);
	ASSERT_EQ(18,this->erModel.componentMap.size());

	Component* connector = new Connector(ComponentData("18",""));
	this->erModel.insertComponent(connector);
	ASSERT_EQ(19,this->erModel.componentMap.size());		
}

TEST_F(ERModelTest,testEraseComponent){
	ASSERT_THROW(this->erModel.eraseComponent(NULL),NullPointerException);

	Component* component = this->erModel.getComponentByID("0");
	this->erModel.eraseComponent(component);
	delete component;

	ASSERT_EQ(14,this->erModel.componentMap.size());
}

TEST_F(ERModelTest,testAddConnection){	
	Component* entityNoteBook = this->erModel.addNode(ComponentType::TypeEntity);
	Component* attributeNoteBookID = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* relationShipOwn = this->erModel.addNode(ComponentType::TypeRelationShip);
	Component* entityDepartment = this->erModel.addNode(ComponentType::TypeEntity);
	Component* attributeDepartmentName = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* relationShipWorkOn = this->erModel.addNode(ComponentType::TypeRelationShip);

	ASSERT_EQ(21,this->erModel.componentMap.size());

	ASSERT_THROW(this->erModel.addConnection(entityNoteBook,NULL),NullPointerException);
	ASSERT_THROW(this->erModel.addConnection(NULL,relationShipOwn),NullPointerException);
	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
	//entity connect to attribute
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->erModel.addConnection(entityNoteBook,attributeNoteBookID));
	ASSERT_THROW(this->erModel.addConnection(entityNoteBook,attributeNoteBookID),HasConnectedException);	
	ASSERT_EQ(true,hasConnected(entityNoteBook,attributeNoteBookID));
	ASSERT_EQ(22,this->erModel.componentMap.size());
	//attribute connect to entity
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->erModel.addConnection(attributeDepartmentName,entityDepartment));
	ASSERT_THROW(this->erModel.addConnection(attributeDepartmentName,entityDepartment),HasConnectedException);
	ASSERT_EQ(true,hasConnected(attributeDepartmentName,entityDepartment));
	ASSERT_EQ(23,this->erModel.componentMap.size());
	//entity connect to relationShip
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->erModel.addConnection(entityNoteBook,relationShipOwn));
	ASSERT_THROW(this->erModel.addConnection(entityNoteBook,relationShipOwn),HasConnectedException);
	ASSERT_EQ(true,hasConnected(entityNoteBook,relationShipOwn));
	ASSERT_EQ(24,this->erModel.componentMap.size());
	//relationShip connect to entity
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->erModel.addConnection(relationShipWorkOn,entityDepartment));
	ASSERT_THROW(this->erModel.addConnection(relationShipWorkOn,entityDepartment),HasConnectedException);
	ASSERT_EQ(true,hasConnected(relationShipWorkOn,entityDepartment));
	ASSERT_EQ(25,this->erModel.componentMap.size());
	//attribute connect to relationShip
	ASSERT_THROW(this->erModel.addConnection(attributeNoteBookID,relationShipOwn),InvalidConnectException);
	ASSERT_EQ(false,hasConnected(attributeNoteBookID,relationShipOwn));
	//relationShip connect to attribute
	ASSERT_THROW(this->erModel.addConnection(relationShipWorkOn,attributeDepartmentName),InvalidConnectException);
	ASSERT_EQ(false,hasConnected(relationShipWorkOn,attributeDepartmentName));
}

TEST_F(ERModelTest,testGetComponentByID){
	ASSERT_THROW(this->erModel.getComponentByID("200"),NoSuchNodeException);
	ASSERT_THROW(this->erModel.getComponentByID("15"),NoSuchNodeException);

	Component* find = this->erModel.getComponentByID("0");
	ASSERT_EQ("0",find->getID());
	ASSERT_EQ("Engineer",find->getName());
	ASSERT_EQ(ComponentType::TypeEntity,find->getType());

	find = this->erModel.getComponentByID("14");
	ASSERT_EQ("14",find->getID());
	ASSERT_EQ("",find->getName());
	ASSERT_EQ(ComponentType::TypeConnector,find->getType());
}

TEST_F(ERModelTest,testGetNodesConnector){
	Component* entityEngineer = this->erModel.componentMap.find("0")->second;
	Component* attributeEmployeeID = this->erModel.componentMap.find("1")->second;
	Component* connectorEngineer = this->erModel.componentMap.find("7")->second;
	Component* entityPC = this->erModel.componentMap.find("4")->second;
	Component* attributePC_ID = this->erModel.componentMap.find("5")->second;
	Component* connectorPC = this->erModel.componentMap.find("9")->second;

	ASSERT_THROW(this->erModel.getNodesConnector(entityEngineer,NULL),NullPointerException);
	ASSERT_THROW(this->erModel.getNodesConnector(NULL,attributeEmployeeID),NullPointerException);
	ASSERT_THROW(this->erModel.getNodesConnector(NULL,NULL),NullPointerException);

	ASSERT_EQ(connectorEngineer,this->erModel.getNodesConnector(entityEngineer,attributeEmployeeID));
	//revert argument order
	ASSERT_EQ(connectorEngineer,this->erModel.getNodesConnector(attributeEmployeeID,entityEngineer));

	ASSERT_EQ(connectorPC,this->erModel.getNodesConnector(entityPC,attributePC_ID));
	//revert argument order
	ASSERT_EQ(connectorPC,this->erModel.getNodesConnector(attributePC_ID,entityPC));

	ASSERT_THROW(this->erModel.getNodesConnector(entityEngineer,attributePC_ID),NullPointerException);
	ASSERT_THROW(this->erModel.getNodesConnector(entityPC,attributeEmployeeID),NullPointerException);
}

TEST_F(ERModelTest,testGetAllComponents){
	ASSERT_EQ(15,this->erModel.getAllComponents().size());

	for each(Component* component in this->erModel.getAllComponents()){
		ASSERT_NE(this->erModel.componentMap.end(),this->erModel.componentMap.find(component->getID()));
	}

	this->erModel.clearComponentMap();

	ASSERT_THROW(this->erModel.getAllComponents(),EmptyCollectionException);
}

TEST_F(ERModelTest,testGetAllConnectors){
	ASSERT_EQ(7,this->erModel.getAllConnectors().size());

	for each(Connector* connector in this->erModel.getAllConnectors()){		
		ASSERT_NE(this->erModel.componentMap.end(),this->erModel.componentMap.find(connector->getID()));
	}

	this->erModel.clearComponentMap();

	ASSERT_THROW(this->erModel.getAllConnectors(),EmptyCollectionException);
}

TEST_F(ERModelTest,testGetAllEntities){
	ASSERT_EQ(2,this->erModel.getAllEntities().size());

	for each(Entity* entity in this->erModel.getAllEntities()){
		ASSERT_NE(this->erModel.componentMap.end(),this->erModel.componentMap.find(entity->getID()));
	}

	this->erModel.clearComponentMap();

	ASSERT_THROW(this->erModel.getAllEntities(),EmptyCollectionException);
}

TEST_F(ERModelTest,testGetAllRelationShips){
	ASSERT_EQ(1,this->erModel.getAllRelationShips().size());

	for each(RelationShip* relationShip in this->erModel.getAllRelationShips()){
		ASSERT_NE(this->erModel.componentMap.end(),this->erModel.componentMap.find(relationShip->getID()));
	}

	this->erModel.clearComponentMap();

	ASSERT_THROW(this->erModel.getAllRelationShips(),EmptyCollectionException);
}

TEST_F(ERModelTest,testGetAllTables){
	unordered_map<string,Table*> tableMap = this->erModel.getAllTables();
	ASSERT_EQ(2,tableMap.size());

	Component* entityEngineer = this->erModel.getComponentByID("0");
	Table* tableEngineer = tableMap.find(entityEngineer->getID())->second;		
	ASSERT_EQ(3,tableEngineer->attributeSet.size());
	ASSERT_EQ(entityEngineer,tableEngineer->entity);
	
	Component* entityPC = this->erModel.getComponentByID("4");
	Table* tablePC = tableMap.find(entityPC->getID())->second;
	ASSERT_EQ(2,tablePC->attributeSet.size());
	ASSERT_EQ(entityPC,tablePC->entity);

	this->erModel.clearComponentMap();

	ASSERT_THROW(this->erModel.getAllTables(),EmptyCollectionException);

}

TEST_F(ERModelTest,testClearComponentMap){	
	ASSERT_EQ(false,this->erModel.componentMap.empty());

	this->erModel.clearComponentMap();

	ASSERT_EQ(true,this->erModel.componentMap.empty());

	Component* attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* entity = this->erModel.addNode(ComponentType::TypeEntity);
	Component* relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	
	ASSERT_EQ(false,this->erModel.componentMap.empty());

	this->erModel.clearComponentMap();
	ASSERT_EQ(true,this->erModel.componentMap.empty());
}