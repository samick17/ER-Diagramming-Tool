#include "ERModelTest.h"
#include "DirectoryUtil.h"
#include "../102598045_POSD/InvalidNodeTypeException.h"
#include "../102598045_POSD/NullPointerException.h"
#include "../102598045_POSD/ComponentType.h"
#include "../102598045_POSD/FileParser.h"

ERModelTest::ERModelTest(){
}

ERModelTest::~ERModelTest(){
}

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


}

TEST_F(ERModelTest,addConnection){
	Component* entity = new Entity(ComponentData("0","Engineer"));
	Component* attribute = new Attribute(ComponentData("1","Name"));
	Component* relationShip = new RelationShip(ComponentData("0","Has"));

	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
	ASSERT_THROW(this->erModel.addConnection(NULL,NULL),NullPointerException);
}

TEST_F(ERModelTest,getComponentByID){
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

	Component* attribute = new Attribute(ComponentData("0","Name"));
	Component* entity = new RelationShip(ComponentData("1","Engineer"));	
	Component* relationShip = new RelationShip(ComponentData("2","Has"));

	this->erModel.componentMap.insert(ComponentPair(attribute->getID(),attribute));
	this->erModel.componentMap.insert(ComponentPair(entity->getID(),entity));
	this->erModel.componentMap.insert(ComponentPair(relationShip->getID(),relationShip));

	ASSERT_EQ(this->erModel.componentMap.empty(),false);

	this->erModel.clearComponentMap();
	ASSERT_EQ(this->erModel.componentMap.empty(),true);
}