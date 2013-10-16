#include "ERModelTest.h"
#include "DirectoryUtil.h"
#include "InvalidNodeTypeException.h"
#include "NullPointerException.h"
#include "NoSuchNodeException.h"
#include "HasConnectedException.h"
#include "InvalidConnectException.h"
#include "ComponentType.h"
#include "FileParser.h"

void ERModelTest::SetUp(){	
	this->erModel = ERModel();
	ASSERT_EQ(this->erModel.componentMap.size(),0);
	
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	_mkdir(directory.c_str());

	string filePath = directory+"/test_file1.erd";
	Document doc(filePath);	
	string fileData[] = {
		"E, Engineer",
		"A, Emp_ID",
		"R, Has",
		"A, Name", 
		"E, PC",
		"A, PC_ID",
		"A, Purchase_Date",
		"C",
		"C",
		"C",
		"C",
		"C, 1",
		"C, 1" ,
		"A, Department",
		"C",
		"",
		"7 0,1",
		"8 0,3",
		"9 4,5",
		"10 4,6",
		"11 0,2",
		"12 2,4",
		"14 0,13",
		"",
		"0 1,3",
		"4 5"
	};
	for (int lineIndex = 0;lineIndex<sizeof(fileData)/sizeof(*fileData);lineIndex++)
		doc.wirteLine(fileData[lineIndex]);

	doc.saveFile();

	FileParser fileParser;
	fileParser.parseFileToModel(filePath,&this->erModel);

	ASSERT_EQ(this->erModel.componentMap.size(),15);
}

void ERModelTest::TearDown(){	
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	string filePath = directory+"/test_file1.erd";
	remove(filePath.c_str());
	_rmdir(directory.c_str());	
}

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

TEST_F(ERModelTest,addNode){	
	ASSERT_THROW(this->erModel.addNode("X"),InvalidNodeTypeException);	
	ASSERT_THROW(this->erModel.addNode("Q"),InvalidNodeTypeException);
	ASSERT_EQ(this->erModel.componentMap.size(),15);

	Component* nodeToAdd = this->erModel.addNode(ComponentType::TypeAttribute);
	ASSERT_EQ(nodeToAdd->getType(),ComponentType::TypeAttribute);
	ASSERT_EQ(this->erModel.componentMap.size(),16);

	nodeToAdd = this->erModel.addNode(ComponentType::TypeEntity);
	ASSERT_EQ(nodeToAdd->getType(),ComponentType::TypeEntity);
	ASSERT_EQ(this->erModel.componentMap.size(),17);

	nodeToAdd = this->erModel.addNode(ComponentType::TypeRelationShip);
	ASSERT_EQ(nodeToAdd->getType(),ComponentType::TypeRelationShip);
	ASSERT_EQ(this->erModel.componentMap.size(),18);

	nodeToAdd = this->erModel.addNode(ComponentType::TypeConnector);
	ASSERT_EQ(nodeToAdd->getType(),ComponentType::TypeConnector);
	ASSERT_EQ(this->erModel.componentMap.size(),19);
}

TEST_F(ERModelTest,insertComponent){
	ASSERT_THROW(this->erModel.insertComponent(NULL),NullPointerException);

	Component* attribute = new Attribute(ComponentData("15","Age"));
	this->erModel.insertComponent(attribute);
	ASSERT_EQ(this->erModel.componentMap.size(),16);
	//insert again~
	this->erModel.insertComponent(attribute);
	ASSERT_EQ(this->erModel.componentMap.size(),16);

	Component* entity = new Entity(ComponentData("16","NoteBook"));
	this->erModel.insertComponent(entity);
	ASSERT_EQ(this->erModel.componentMap.size(),17);

	Component* relationShip = new RelationShip(ComponentData("17","Work on"));
	this->erModel.insertComponent(relationShip);
	ASSERT_EQ(this->erModel.componentMap.size(),18);

	Component* connector = new Connector(ComponentData("18",""));
	this->erModel.insertComponent(connector);
	ASSERT_EQ(this->erModel.componentMap.size(),19);		
}

TEST_F(ERModelTest,eraseComponent){
	ASSERT_THROW(this->erModel.eraseComponent(NULL),NullPointerException);

	Component* component = this->erModel.getComponentByID("0");
	this->erModel.eraseComponent(component);
	delete component;

	ASSERT_EQ(this->erModel.componentMap.size(),14);
}

TEST_F(ERModelTest,addConnection){
	
	Component* entityNoteBook = this->erModel.addNode(ComponentType::TypeEntity);
	Component* attributeNoteBookID = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* relationShipOwn = this->erModel.addNode(ComponentType::TypeRelationShip);
	Component* entityDepartment = this->erModel.addNode(ComponentType::TypeEntity);
	Component* attributeDepartmentName = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* relationShipWorkOn = this->erModel.addNode(ComponentType::TypeRelationShip);

	ASSERT_EQ(this->erModel.componentMap.size(),21);

	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
	//entity connect to attribute
	ASSERT_EQ(this->erModel.addConnection(entityNoteBook,attributeNoteBookID),NodeConnectionType::ValidConnect);
	ASSERT_THROW(this->erModel.addConnection(entityNoteBook,attributeNoteBookID),HasConnectedException);	
	ASSERT_EQ(hasConnected(entityNoteBook,attributeNoteBookID),true);
	ASSERT_EQ(this->erModel.componentMap.size(),22);
	//attribute connect to entity
	ASSERT_EQ(this->erModel.addConnection(attributeDepartmentName,entityDepartment),NodeConnectionType::ValidConnect);
	ASSERT_THROW(this->erModel.addConnection(attributeDepartmentName,entityDepartment),HasConnectedException);
	ASSERT_EQ(hasConnected(attributeDepartmentName,entityDepartment),true);
	ASSERT_EQ(this->erModel.componentMap.size(),23);
	//entity connect to relationShip
	ASSERT_EQ(this->erModel.addConnection(entityNoteBook,relationShipOwn),NodeConnectionType::ConnectEntityAndRelation);
	ASSERT_THROW(this->erModel.addConnection(entityNoteBook,relationShipOwn),HasConnectedException);
	ASSERT_EQ(hasConnected(entityNoteBook,relationShipOwn),true);
	ASSERT_EQ(this->erModel.componentMap.size(),24);
	//relationShip connect to entity
	ASSERT_EQ(this->erModel.addConnection(relationShipWorkOn,entityDepartment),NodeConnectionType::ConnectEntityAndRelation);
	ASSERT_THROW(this->erModel.addConnection(relationShipWorkOn,entityDepartment),HasConnectedException);
	ASSERT_EQ(hasConnected(relationShipWorkOn,entityDepartment),true);
	ASSERT_EQ(this->erModel.componentMap.size(),25);
	//attribute connect to relationShip
	ASSERT_THROW(this->erModel.addConnection(attributeNoteBookID,relationShipOwn),InvalidConnectException);
	ASSERT_EQ(hasConnected(attributeNoteBookID,relationShipOwn),false);
	//relationShip connect to attribute
	ASSERT_THROW(this->erModel.addConnection(relationShipWorkOn,attributeDepartmentName),InvalidConnectException);
	ASSERT_EQ(hasConnected(relationShipWorkOn,attributeDepartmentName),false);
}

TEST_F(ERModelTest,getComponentByID){
	ASSERT_THROW(this->erModel.getComponentByID("200"),NoSuchNodeException);
	ASSERT_THROW(this->erModel.getComponentByID("15"),NoSuchNodeException);

	Component* find = this->erModel.getComponentByID("0");
	ASSERT_EQ(find->getID(),"0");
	ASSERT_EQ(find->getName(),"Engineer");
	ASSERT_EQ(find->getType(),ComponentType::TypeEntity);

	find = this->erModel.getComponentByID("14");
	ASSERT_EQ(find->getID(),"14");
	ASSERT_EQ(find->getName(),"");
	ASSERT_EQ(find->getType(),ComponentType::TypeConnector);
}

TEST_F(ERModelTest,getNodesConnector){

}

TEST_F(ERModelTest,getAllComponents){
}

TEST_F(ERModelTest,getAllConnectors){
}

TEST_F(ERModelTest,getAllEntities){
}

TEST_F(ERModelTest,getAllRelationShips){
}

TEST_F(ERModelTest,getAllTables){
	
}

TEST_F(ERModelTest,clearComponentMap){	
	ASSERT_EQ(this->erModel.componentMap.empty(),false);

	this->erModel.clearComponentMap();

	ASSERT_EQ(this->erModel.componentMap.empty(),true);

	Component* attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* entity = this->erModel.addNode(ComponentType::TypeEntity);
	Component* relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	
	ASSERT_EQ(this->erModel.componentMap.empty(),false);

	this->erModel.clearComponentMap();
	ASSERT_EQ(this->erModel.componentMap.empty(),true);
}