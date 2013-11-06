#include "ERModelTest.h"
#include "DirectoryUtil.h"
#include "InvalidNodeTypeException.h"
#include "NullPointerException.h"
#include "NoSuchNodeException.h"
#include "HasConnectedException.h"
#include "InvalidConnectException.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"
#include "InputFileParser.h"
#include "EmptyCollectionException.h"
#include "FileCreator.h"

void ERModelTest::SetUp(){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());

    Entity* entityEngineer = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    Attribute* attributeEmp_ID = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    RelationShip* relationShipHas = static_cast<RelationShip*>(this->erModel.addNode(ComponentType::TypeRelationShip));
    Attribute* attributeName = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    Entity* entityPC = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    Attribute* attributePC_ID = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    Attribute* attributePurchase_Date = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
        
    this->erModel.addConnection(entityEngineer,attributeEmp_ID);
    this->erModel.addConnection(entityEngineer,attributeName);
    this->erModel.addConnection(entityPC,attributePC_ID);
    this->erModel.addConnection(entityPC,attributePurchase_Date);
    this->erModel.addConnection(entityEngineer,relationShipHas);
    this->erModel.addConnection(relationShipHas,entityPC);
    Attribute* attributeDepartment = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));    
    this->erModel.addConnection(entityEngineer,attributeDepartment);
    this->erModel.getComponentByID("11")->setName(RelationType::OneToOne);
    this->erModel.getComponentByID("12")->setName(RelationType::OneToOne);    
    attributeEmp_ID->setAsPrimaryKey();
    attributeName->setAsPrimaryKey();    
    attributePC_ID->setAsPrimaryKey();

    entityEngineer->setName("Engineer");
    attributeEmp_ID->setName("Emp_ID");
    relationShipHas->setName("Has");
    attributeName->setName("Name");
    entityPC->setName("PC");
    attributePC_ID->setName("PC_ID");
    attributePurchase_Date->setName("Purchase_Date");
    attributeDepartment->setName("Department");

    ASSERT_EQ(15,this->erModel.componentMap.size());
}

//return firstComponent has connection to secondComponent & secondComponent has connection to firstComponent
bool ERModelTest::hasConnected(Component* firstComponent,Component* secondComponent){
    bool isFirstComponentConnectToSecond = false;
    bool isSecondComponentConnectToFirst = false;

    for each(Component* connector in firstComponent->connectionMap){
        if(connector->connectionMap.containsKey(secondComponent->getID()))
            isFirstComponentConnectToSecond = true;
    }

    for each(Component* connector in secondComponent->connectionMap){
        if(connector->connectionMap.containsKey(firstComponent->getID()))
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
    Component* attribute = new Attribute(ComponentData("15","Age"));
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

TEST_F(ERModelTest,testOpenFile){
    string filePath = FileCreator::createDefaultFile();

    this->erModel.openFile(filePath);
    ASSERT_EQ(15,this->erModel.getAllComponents().size());
    ASSERT_THROW(this->erModel.commandManager.redo(),Exception);
    ASSERT_THROW(this->erModel.commandManager.undo(),Exception);

    FileCreator::deleteDefaultFile();
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

    ASSERT_THROW(this->erModel.getNodesConnector(entityEngineer,attributePC_ID),NullPointerException);
    ASSERT_THROW(this->erModel.getNodesConnector(entityPC,attributeEmployeeID),NullPointerException);
}

TEST_F(ERModelTest,testGetAllComponents){
    ASSERT_EQ(15,this->erModel.getAllComponents().size());

    for each(Component* component in this->erModel.getAllComponents()){
    }

    this->erModel.clearComponentMap();

    ASSERT_EQ(0,this->erModel.getAllComponents().size());
}

TEST_F(ERModelTest,testGetAllConnectors){
    ASSERT_EQ(7,this->erModel.getAllConnectors().size());

    for each(Connector* connector in this->erModel.getAllConnectors()){
    }

    this->erModel.clearComponentMap();

    ASSERT_EQ(0,this->erModel.getAllConnectors().size());
}

TEST_F(ERModelTest,testGetAllEntities){
    ASSERT_EQ(2,this->erModel.getAllEntities().size());

    for each(Entity* entity in this->erModel.getAllEntities()){
    }

    this->erModel.clearComponentMap();

    ASSERT_EQ(0,this->erModel.getAllEntities().size());
}

TEST_F(ERModelTest,testGetAllRelationShips){
    ASSERT_EQ(1,this->erModel.getAllRelationShips().size());

    for each(RelationShip* relationShip in this->erModel.getAllRelationShips()){
    }

    this->erModel.clearComponentMap();

    ASSERT_EQ(0,this->erModel.getAllRelationShips().size());
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

    this->erModel.clearComponentMap();

    ASSERT_EQ(0,this->erModel.getAllTables().size());

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