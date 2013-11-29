#include "ERModelTest.h"
#include "DirectoryUtil.h"
#include "InvalidNodeTypeException.h"
#include "NullPointerException.h"
#include "NoSuchNodeException.h"
#include "NoConnectionException.h"
#include "HasConnectedException.h"
#include "InvalidConnectException.h"
#include "EmptyCollectionException.h"
#include "FileNotFoundException.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"
#include "InputFileParser.h"
#include "FileCreator.h"
#include "Presentation.h"
#include "TextPresentation.h"

void ERModelTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->textPresentation = new TextPresentation(this->presentation);
    //this->textUIPresenter = new TextUIPresenter(this->textPresentation);
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
    ASSERT_EQ(RelationType::One,this->erModel.componentMap.get("11")->getName());
    ASSERT_EQ(RelationType::One,this->erModel.componentMap.get("12")->getName());
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

void ERModelTest::TearDown(){
    //delete file
    FileCreator::deleteDefaultFile();
    //delete pointer
    delete this->presentation;
    delete this->textPresentation;
}

//return firstComponent has connection to secondComponent & secondComponent has connection to firstComponent
bool ERModelTest::hasConnected(Component* firstComponent,Component* secondComponent){
    bool isFirstComponentConnectToSecond = false;
    bool isSecondComponentConnectToFirst = false;

    for each(Component* connector in firstComponent->connectionMap)
        if(connector->connectionMap.containsKey(secondComponent->getID()))
            isFirstComponentConnectToSecond = true;

    for each(Component* connector in secondComponent->connectionMap)
        if(connector->connectionMap.containsKey(firstComponent->getID()))
            isSecondComponentConnectToFirst = true;

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
    ASSERT_THROW(this->erModel.addNode(ComponentType::TypeConnector),InvalidNodeTypeException);
    ASSERT_EQ(18,this->erModel.componentMap.size());
}

TEST_F(ERModelTest,testInsertComponent){
    Component* attribute = new Attribute("15","Age");
    this->erModel.insertComponent(attribute);
    ASSERT_EQ(16,this->erModel.componentMap.size());
    ASSERT_EQ(attribute,this->erModel.componentMap.get("15"));

    Component* entity = new Entity("16","NoteBook");
    this->erModel.insertComponent(entity);
    ASSERT_EQ(17,this->erModel.componentMap.size());
    ASSERT_EQ(entity,this->erModel.componentMap.get("16"));

    Component* relationShip = new RelationShip("17","Work on");
    this->erModel.insertComponent(relationShip);
    ASSERT_EQ(18,this->erModel.componentMap.size());
    ASSERT_EQ(relationShip,this->erModel.componentMap.get("17"));

    Component* connector = new Connector("18");
    this->erModel.insertComponent(connector);
    ASSERT_EQ(19,this->erModel.componentMap.size());
    ASSERT_EQ(connector,this->erModel.componentMap.get("18"));
}

TEST_F(ERModelTest,testInsertComponentAt){
    Component* lastComponent = this->erModel.getComponentByID("14");
    this->erModel.eraseComponent(lastComponent);

    this->erModel.insertComponentAt(lastComponent,0);
    ASSERT_EQ(lastComponent,*this->erModel.getAllComponents().begin());

    this->erModel.eraseComponent(lastComponent);

    this->erModel.insertComponentAt(lastComponent,this->erModel.getAllComponents().size());
    ASSERT_EQ(lastComponent,*--this->erModel.getAllComponents().end());
}

TEST_F(ERModelTest,testEraseComponent){
    Component* componentToDelete1 = this->erModel.getComponentByID("0");
    this->erModel.eraseComponent(componentToDelete1);
    delete componentToDelete1;
    ASSERT_EQ(14,this->erModel.componentMap.size());
    ASSERT_THROW(this->erModel.componentMap.get("0"),NoSuchKeyException);

    Component* componentToDelete2 = this->erModel.getComponentByID("14");
    this->erModel.eraseComponent(componentToDelete2);
    delete componentToDelete2;
    ASSERT_EQ(13,this->erModel.componentMap.size());
    ASSERT_THROW(this->erModel.componentMap.get("14"),NoSuchKeyException);
}

TEST_F(ERModelTest,testAddConnection){
    Component* entityNoteBook = this->erModel.addNode(ComponentType::TypeEntity);
    Component* attributeNoteBookID = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* relationShipOwn = this->erModel.addNode(ComponentType::TypeRelationShip);
    Component* entityDepartment = this->erModel.addNode(ComponentType::TypeEntity);
    Component* attributeDepartmentName = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* relationShipWorkOn = this->erModel.addNode(ComponentType::TypeRelationShip);

    ASSERT_EQ(21,this->erModel.componentMap.size());

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

TEST_F(ERModelTest,testSetCardinality){
    Connector* connector = static_cast<Connector*>(this->erModel.getComponentByID("9"));

    string expectedCardinality = RelationType::One;
    ASSERT_EQ(true,this->erModel.setCardinality(connector,expectedCardinality));
    ASSERT_EQ(expectedCardinality,connector->getName());
    expectedCardinality = RelationType::Many;
    ASSERT_EQ(true,this->erModel.setCardinality(connector,expectedCardinality));
    ASSERT_EQ(expectedCardinality,connector->getName());
    expectedCardinality = "WrongCardinality";
    string originConnectorName = connector->getName();
    ASSERT_EQ(false,this->erModel.setCardinality(connector,expectedCardinality));
    ASSERT_EQ(originConnectorName,connector->getName());
}

TEST_F(ERModelTest,testSetPrimaryKey){
    //test set primaryKey to Attribute,which is not exists
    ASSERT_THROW(this->erModel.setPrimaryKey("X"),NoSuchNodeException);
    //test set primaryKey to Attribute,which is connected to an Entity
    Attribute* attribute = static_cast<Attribute*>(this->erModel.getComponentByID("1"));
    bool isPrimaryKey = attribute->isPrimaryKey();

    //test set primaryKey
    this->erModel.setPrimaryKey(attribute->getID());
    ASSERT_EQ(!isPrimaryKey,attribute->isPrimaryKey());
    //test set primaryKey again
    this->erModel.setPrimaryKey(attribute->getID());
    ASSERT_EQ(isPrimaryKey,attribute->isPrimaryKey());

    //test set primaryKey to Attribute, which is 'not' connected to an Entity
    attribute = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    isPrimaryKey = attribute->isPrimaryKey();
    //test set primaryKey
    ASSERT_THROW(this->erModel.setPrimaryKey(attribute->getID()),NoConnectionException);
}

TEST_F(ERModelTest,testSetComponentText){
    //test set component,which is not exists

    ASSERT_THROW(this->erModel.setComponentText("X","testTextX"),NoSuchNodeException);
    ASSERT_THROW(this->erModel.setComponentText("Y","testTestTestY"),NoSuchNodeException);

    //test set attribute text
    Component* attribute = this->erModel.getComponentByID("4");
    this->erModel.setComponentText(attribute->getID(),"testAttributeText");
    ASSERT_EQ("testAttributeText",attribute->getName());
    //test set entity text
    Component* entity = this->erModel.getComponentByID("5");
    this->erModel.setComponentText(entity->getID(),"testEntityText");
    ASSERT_EQ("testEntityText",entity->getName());
    //test set relationShip text
    Component* relationShip = this->erModel.getComponentByID("3");
    this->erModel.setComponentText(relationShip->getID(),"testRelationShipText");
    ASSERT_EQ("testRelationShipText",relationShip->getName());
    //test set connector text,with right cadinality
    Component* connector = this->erModel.getComponentByID("12");
    this->erModel.setComponentText(connector->getID(),RelationType::One);
    ASSERT_EQ(RelationType::One,connector->getName());
    //test set connector text,with right cadinality
    this->erModel.setComponentText(connector->getID(),RelationType::Many);
    ASSERT_EQ(RelationType::Many,connector->getName());
    //test set connector text,with wrong cadinality
    this->erModel.setComponentText(connector->getID(),"X");
    ASSERT_EQ(RelationType::Many,connector->getName());
    //test set connector text,which is connected to attribute & entity
    connector = this->erModel.getComponentByID("8");
    string originConnectorName = connector->getName();
    this->erModel.setComponentText(connector->getID(),RelationType::One);
    ASSERT_EQ(originConnectorName,connector->getName());
    this->erModel.setComponentText(connector->getID(),RelationType::Many);
    ASSERT_EQ(originConnectorName,connector->getName());
    this->erModel.setComponentText(connector->getID(),"X");
    ASSERT_EQ(originConnectorName,connector->getName());
}

TEST_F(ERModelTest,testOpenFile){
    string filePath = FileCreator::createDefaultFile();

    this->erModel.openFile(filePath);
    ASSERT_EQ(15,this->erModel.getAllComponents().size());
    ASSERT_THROW(this->erModel.commandManager.redo(),Exception);
    ASSERT_THROW(this->erModel.commandManager.undo(),Exception);

    //test openfile again
    this->erModel.openFile(filePath);
    ASSERT_EQ(15,this->erModel.getAllComponents().size());
    ASSERT_THROW(this->erModel.commandManager.redo(),Exception);
    ASSERT_THROW(this->erModel.commandManager.undo(),Exception);

    FileCreator::deleteDefaultFile();
}

TEST_F(ERModelTest,testSaveFile){
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
    Component* entityEngineer = this->erModel.componentMap.get("0");
    Component* attributeEmployeeID = this->erModel.componentMap.get("1");
    Component* connectorEngineer = this->erModel.componentMap.get("7");
    Component* entityPC = this->erModel.componentMap.get("4");
    Component* attributePC_ID = this->erModel.componentMap.get("5");
    Component* connectorPC = this->erModel.componentMap.get("9");

    ASSERT_EQ(connectorEngineer,this->erModel.getNodesConnector(entityEngineer,attributeEmployeeID));
    //revert argument order
    ASSERT_EQ(connectorEngineer,this->erModel.getNodesConnector(attributeEmployeeID,entityEngineer));

    ASSERT_EQ(connectorPC,this->erModel.getNodesConnector(entityPC,attributePC_ID));
    //revert argument order
    ASSERT_EQ(connectorPC,this->erModel.getNodesConnector(attributePC_ID,entityPC));

    ASSERT_EQ(NULL,this->erModel.getNodesConnector(entityEngineer,attributePC_ID));
    ASSERT_EQ(NULL,this->erModel.getNodesConnector(entityPC,attributeEmployeeID));
}

TEST_F(ERModelTest,testGetAllComponents){
    ASSERT_EQ(15,this->erModel.getAllComponents().size());
    ASSERT_EQ(this->erModel.componentMap,this->erModel.getAllComponents());
}

TEST_F(ERModelTest,testGetAllConnectors){
    HashMap<string,Connector*> connectorMap = this->erModel.getAllConnectors();
    ASSERT_EQ(7,connectorMap.size());
    ASSERT_EQ(connectorMap.get("7"),this->erModel.componentMap.get("7"));
    ASSERT_EQ(connectorMap.get("8"),this->erModel.componentMap.get("8"));
    ASSERT_EQ(connectorMap.get("9"),this->erModel.componentMap.get("9"));
    ASSERT_EQ(connectorMap.get("10"),this->erModel.componentMap.get("10"));
    ASSERT_EQ(connectorMap.get("11"),this->erModel.componentMap.get("11"));
    ASSERT_EQ(connectorMap.get("12"),this->erModel.componentMap.get("12"));
    ASSERT_EQ(connectorMap.get("14"),this->erModel.componentMap.get("14"));
}

TEST_F(ERModelTest,testGetAllAttributes){
    HashMap<string,Attribute*> attributeMap = this->erModel.getAllAttributes();
    ASSERT_EQ(5,attributeMap.size());
    ASSERT_EQ(attributeMap.get("1"),this->erModel.componentMap.get("1"));
    ASSERT_EQ(attributeMap.get("3"),this->erModel.componentMap.get("3"));
    ASSERT_EQ(attributeMap.get("5"),this->erModel.componentMap.get("5"));
    ASSERT_EQ(attributeMap.get("6"),this->erModel.componentMap.get("6"));
    ASSERT_EQ(attributeMap.get("13"),this->erModel.componentMap.get("13"));
}

TEST_F(ERModelTest,testGetAllEntities){
    HashMap<string,Entity*> entityMap = this->erModel.getAllEntities();
    ASSERT_EQ(2,entityMap.size());
    ASSERT_EQ(entityMap.get("0"),this->erModel.componentMap.get("0"));
    ASSERT_EQ(entityMap.get("4"),this->erModel.componentMap.get("4"));
}

TEST_F(ERModelTest,testGetAllRelationShips){
    HashMap<string,RelationShip*> relationShipMap = this->erModel.getAllRelationShips();
    ASSERT_EQ(1,relationShipMap.size());
    ASSERT_EQ(relationShipMap.get("2"),this->erModel.componentMap.get("2"));
}

TEST_F(ERModelTest,testGetAllTables){
    HashMap<string,Table*> tableMap = this->erModel.getAllTables();
    ASSERT_EQ(2,tableMap.size());

    Component* entityEngineer = this->erModel.getComponentByID("0");
    Table* tableEngineer = tableMap.get(entityEngineer->getID());
    ASSERT_EQ(3,tableEngineer->attributeMap.size());
    ASSERT_EQ(entityEngineer,tableEngineer->entity);
    
    Component* entityPC = this->erModel.getComponentByID("4");
    Table* tablePC = tableMap.get(entityPC->getID());
    ASSERT_EQ(2,tablePC->attributeMap.size());
    ASSERT_EQ(entityPC,tablePC->entity);
}

TEST_F(ERModelTest,testResetERModel){
    ASSERT_EQ(false,this->erModel.componentMap.empty());

    this->erModel.resetERModel();
    ASSERT_EQ(true,this->erModel.componentMap.empty());
    ASSERT_THROW(this->erModel.commandManager.redo(),Exception);
    ASSERT_THROW(this->erModel.commandManager.undo(),Exception);

    Component* attribute = this->erModel.addNode(ComponentType::TypeAttribute);
    Component* entity = this->erModel.addNode(ComponentType::TypeEntity);
    Component* relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
    
    ASSERT_EQ(false,this->erModel.componentMap.empty());
    this->erModel.resetERModel();
    ASSERT_EQ(true,this->erModel.componentMap.empty());
    ASSERT_THROW(this->erModel.commandManager.redo(),Exception);
    ASSERT_THROW(this->erModel.commandManager.undo(),Exception);
}
/***************************************************************************/
/*                      Integration Test                                   */
/***************************************************************************/
TEST_F(ERModelTest,testLoadFileNotExist){
    string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
    string filePath = directory+"/file_not_exist.erd";
    InputFileParser inputFileParser;
    ASSERT_THROW(inputFileParser.parseFileToModel(filePath,&this->erModel),FileNotFoundException);
}

TEST_F(ERModelTest,testIsPrimaryExist){
    //ASSERT table
    HashMap<string,Table*> tableMap = this->erModel.getAllTables();
    ASSERT_EQ(2,tableMap.size());
    ASSERT_EQ(1,tableMap.get("0")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("0")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(0,tableMap.get("0")->getAllForeignKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("4")->getAllForeignKeyAttributesNameVector().size());

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

TEST_F(ERModelTest,testUndoDeleteComponent){
    Entity* entityTest = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    entityTest->setName("Test");

    ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
    ASSERT_EQ(16,this->erModel.componentMap.size());

    this->erModel.deleteComponent(entityTest->getID());
        
    ASSERT_THROW(this->erModel.componentMap.get(entityTest->getID()),NoSuchKeyException);
    ASSERT_EQ(15,this->erModel.componentMap.size());

    this->erModel.undo();

    ASSERT_EQ(entityTest,this->erModel.componentMap.get(entityTest->getID()));
    ASSERT_EQ(16,this->erModel.componentMap.size());
}

TEST_F(ERModelTest,testRedoConnectComponent){
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

TEST_F(ERModelTest,testCommonUsage){
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
    connectorNode0AndNode6->setName(RelationType::One);
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
    entityWorkDiary->setPrimaryKey(attributeWD_ID->getID());
    ASSERT_EQ(1,entityWorkDiary->getPrimaryKeyAttributes().size());
    ASSERT_EQ(attributeWD_ID,entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID()));
    ASSERT_EQ("WD_ID",entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID())->getName());
    //ASSERT table
    HashMap<string,Table*> tableMap = this->erModel.getAllTables();
    ASSERT_EQ(3,tableMap.size());
    ASSERT_EQ(1,tableMap.get("0")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("0")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(0,tableMap.get("0")->getAllForeignKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("4")->getAllForeignKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("15")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("15")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(0,tableMap.get("15")->getAllForeignKeyAttributesNameVector().size());
    //Assert "Work Diary" exists
    ASSERT_EQ(entityWorkDiary,this->erModel.getComponentByID(entityWorkDiary->getID()));
    //Assert "Work Diary" primary key is "WD_ID"
    ASSERT_EQ(attributeWD_ID,entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID()));
    ASSERT_EQ("WD_ID",entityWorkDiary->getPrimaryKeyAttributes().get(attributeWD_ID->getID())->getName());

    this->erModel.deleteComponent(entityWorkDiary->getID());

    //Assert there is no such node "Work Diary"
    ASSERT_THROW(this->erModel.getComponentByID(entityWorkDiary->getID()),NoSuchNodeException);
    //ASSERT there is no connection between node 15 and 16
    ASSERT_EQ(NULL,this->erModel.getNodesConnector(entityWorkDiary,node16));
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node16));
    ASSERT_EQ(false,node16->hasConnectedTo(entityWorkDiary));
    //ASSERT there is no connection between node 15 and 19
    ASSERT_EQ(NULL,this->erModel.getNodesConnector(entityWorkDiary,node19));
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node19));
    ASSERT_EQ(false,node19->hasConnectedTo(entityWorkDiary));
    //ASSERT there is no connection between node 15 and 20
    ASSERT_EQ(NULL,this->erModel.getNodesConnector(entityWorkDiary,node20));
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node20));
    ASSERT_EQ(false,node20->hasConnectedTo(entityWorkDiary));
    //ASSERT there is no connection between node 15 and 21
    ASSERT_EQ(NULL,this->erModel.getNodesConnector(entityWorkDiary,node21));
    ASSERT_EQ(false,entityWorkDiary->hasConnectedTo(node21));
    ASSERT_EQ(false,node21->hasConnectedTo(entityWorkDiary));
    //ASSERT table
    tableMap = this->erModel.getAllTables();
    ASSERT_EQ(2,tableMap.size());
    ASSERT_EQ(1,tableMap.get("0")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("0")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(0,tableMap.get("0")->getAllForeignKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("4")->getAllForeignKeyAttributesNameVector().size());
    //Assert there is no such node "Work Diary"
    ASSERT_THROW(this->erModel.getComponentByID(entityWorkDiary->getID()),NoSuchNodeException);
    //Assert Engineer's primary key is "Name" and "Emp_ID"
    Entity* entityEngineer = static_cast<Entity*>(this->erModel.getComponentByID("0"));
    ASSERT_EQ(this->erModel.getComponentByID("1"),entityEngineer->getPrimaryKeyAttributes().get("1"));
    ASSERT_EQ(this->erModel.getComponentByID("3"),entityEngineer->getPrimaryKeyAttributes().get("3"));
    //Undo
    this->erModel.undo();
    //ASSERT table
    tableMap = this->erModel.getAllTables();
    ASSERT_EQ(3,tableMap.size());
    ASSERT_EQ(1,tableMap.get("0")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("0")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(0,tableMap.get("0")->getAllForeignKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("4")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("4")->getAllForeignKeyAttributesNameVector().size());
    ASSERT_EQ(2,tableMap.get("15")->getAllDefaultKeyAttributesNameVector().size());
    ASSERT_EQ(1,tableMap.get("15")->getAllPrimaryKeyAttributesNameVector().size());
    ASSERT_EQ(0,tableMap.get("15")->getAllForeignKeyAttributesNameVector().size());
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