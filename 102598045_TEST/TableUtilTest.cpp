#include "TableUtilTest.h"
#include "ComponentUtil.h"

void TableUtilTest::SetUp(){
    Entity* entityEngineer = new Entity("0","Engineer");//0
    Attribute* attributeName = new Attribute("1","Name");//1
    Entity* entityPC = new Entity("2","PC");//2
    Attribute* attributeEmp_ID = new Attribute("3","Emp_ID");//3
    Entity* entityNoteBook = new Entity("4","NoteBook");//4
    Connector* connector1 = new Connector("5");//5 0 1
    Connector* connector2 = new Connector("6");//6 0 3
    RelationShip* relationShipHas1 = new RelationShip("7","Has");//7
    Connector* connector3 = new Connector("8");//8 0 7
    Connector* connector4 = new Connector("9");//9 2 7
    Attribute* attributeNoteBook_ID = new Attribute("10","NoteBook_ID");//10
    Attribute* attributePC_ID = new Attribute("11","PC_ID");//11
    Attribute* attributePurchase_Date = new Attribute("12","Purchase_Date");//12
    RelationShip* relationShipHas2 = new RelationShip("13","Has");//13
    Connector* connector5 = new Connector("14");//14 4 10
    Connector* connector6 = new Connector("15");//15 11 2
    Connector* connector7 = new Connector("16");//16 12 2
    Connector* connector8 = new Connector("17");//17 0 13
    Connector* connector9 = new Connector("18");//18 4 13
    Entity* entityTest = new Entity("19","Test Entity");//19

    this->entityMap.put(entityEngineer->getID(),entityEngineer);
    this->entityMap.put(entityPC->getID(),entityPC);
    this->entityMap.put(entityNoteBook->getID(),entityNoteBook);
    this->entityMap.put(entityTest->getID(),entityTest);

    this->attributeMap.put(attributeName->getID(),attributeName);
    this->attributeMap.put(attributeEmp_ID->getID(),attributeEmp_ID);
    this->attributeMap.put(attributeNoteBook_ID->getID(),attributeNoteBook_ID);
    this->attributeMap.put(attributePC_ID->getID(),attributePC_ID);
    this->attributeMap.put(attributePurchase_Date->getID(),attributePurchase_Date);

    this->relationShipMap.put(relationShipHas1->getID(),relationShipHas1);
    this->relationShipMap.put(relationShipHas2->getID(),relationShipHas2);

    this->connectorMap.put(connector1->getID(),connector1);
    this->connectorMap.put(connector2->getID(),connector2);
    this->connectorMap.put(connector3->getID(),connector3);
    this->connectorMap.put(connector4->getID(),connector4);
    this->connectorMap.put(connector5->getID(),connector5);
    this->connectorMap.put(connector6->getID(),connector6);
    this->connectorMap.put(connector7->getID(),connector7);
    this->connectorMap.put(connector8->getID(),connector8);
    this->connectorMap.put(connector9->getID(),connector9);

    ComponentUtil::connectWithEachOther(entityEngineer,attributeName,connector1);
    ComponentUtil::connectWithEachOther(entityEngineer,attributeEmp_ID,connector2);
    ComponentUtil::connectWithEachOther(entityEngineer,relationShipHas1,connector3);
    ComponentUtil::connectWithEachOther(entityPC,relationShipHas1,connector4);

    ComponentUtil::connectWithEachOther(entityNoteBook,attributeNoteBook_ID,connector5);
    ComponentUtil::connectWithEachOther(attributePC_ID,attributePC_ID,connector6);
    ComponentUtil::connectWithEachOther(attributePurchase_Date,attributePurchase_Date,connector7);
    ComponentUtil::connectWithEachOther(entityEngineer,relationShipHas2,connector8);
    ComponentUtil::connectWithEachOther(entityNoteBook,relationShipHas2,connector9);
}

void TableUtilTest::TearDown(){
    clearAllMap();
}

void TableUtilTest::clearAllMap(){
    for each(Attribute* attribute in this->attributeMap)
        delete attribute;
    this->attributeMap.clear();
    for each(Entity* entity in this->entityMap)
        delete entity;
    this->entityMap.clear();
    for each(RelationShip* relationShip in this->relationShipMap)
        delete relationShip;
    this->relationShipMap.clear();
    for each(Connector* connector in this->connectorMap)
        delete connector;
    this->connectorMap.clear();
}

TEST_F(TableUtilTest,testConvertToTableMap){
    TableUtil::convertToTableMap(this->tableManager,this->entityMap,this->relationShipMap);
    ASSERT_EQ(4,this->tableManager.getAllTables().size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("0")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("2")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("4")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("19")->foreignKeyAttributeMap.size());

    this->connectorMap.get("8")->setName(RelationType::One);
    this->connectorMap.get("9")->setName(RelationType::One);
    this->connectorMap.get("17")->setName(RelationType::One);
    this->connectorMap.get("18")->setName(RelationType::One);
    this->attributeMap.get("1")->setAsPrimaryKey();
    this->attributeMap.get("10")->setAsPrimaryKey();
    TableUtil::convertToTableMap(this->tableManager,this->entityMap,this->relationShipMap);

    ASSERT_EQ(4,this->tableManager.getAllTables().size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("0")->foreignKeyAttributeMap.size());
    ASSERT_EQ(1,this->tableManager.getAllTables().get("2")->foreignKeyAttributeMap.size());
    ASSERT_EQ(1,this->tableManager.getAllTables().get("4")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("19")->foreignKeyAttributeMap.size());

    
    this->attributeMap.get("11")->setAsPrimaryKey();
    this->attributeMap.get("3")->setAsPrimaryKey();
    TableUtil::convertToTableMap(this->tableManager,this->entityMap,this->relationShipMap);
    ASSERT_EQ(4,this->tableManager.getAllTables().size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("0")->foreignKeyAttributeMap.size());
    ASSERT_EQ(2,this->tableManager.getAllTables().get("2")->foreignKeyAttributeMap.size());
    ASSERT_EQ(2,this->tableManager.getAllTables().get("4")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("19")->foreignKeyAttributeMap.size());
}

TEST_F(TableUtilTest,testConvertEmptyMap){
    ASSERT_EQ(0,this->tableManager.getAllTables().size());
    clearAllMap();
    TableUtil::insertAllEntitiesToTable(this->tableManager,this->entityMap);
    ASSERT_EQ(0,this->tableManager.getAllTables().size());
}

TEST_F(TableUtilTest,testInsertAllEntitiesToTable){
    ASSERT_EQ(0,this->tableManager.getAllTables().size());
    TableUtil::insertAllEntitiesToTable(this->tableManager,this->entityMap);
    ASSERT_EQ(4,this->tableManager.getAllTables().size());
    ASSERT_EQ(this->entityMap.get("0"),this->tableManager.getAllTables().get("0")->node);
    ASSERT_EQ(this->entityMap.get("2"),this->tableManager.getAllTables().get("2")->node);
    ASSERT_EQ(this->entityMap.get("4"),this->tableManager.getAllTables().get("4")->node);
    ASSERT_EQ(this->entityMap.get("19"),this->tableManager.getAllTables().get("19")->node);
}

TEST_F(TableUtilTest,testGetOneToOneRelationShips){
    HashMap<string,RelationShip*> relationMapToAssert = TableUtil::getOneToOneRelationShips(this->relationShipMap);
    ASSERT_EQ(0,relationMapToAssert.size());
    this->connectorMap.get("8")->setName(RelationType::One);
    this->connectorMap.get("9")->setName(RelationType::One);
    relationMapToAssert = TableUtil::getOneToOneRelationShips(this->relationShipMap);
    ASSERT_EQ(1,relationMapToAssert.size());
    ASSERT_EQ(this->relationShipMap.get("7"),relationMapToAssert.get("7"));
    this->connectorMap.get("17")->setName(RelationType::One);
    this->connectorMap.get("18")->setName(RelationType::One);
    relationMapToAssert = TableUtil::getOneToOneRelationShips(this->relationShipMap);
    ASSERT_EQ(2,relationMapToAssert.size());
    ASSERT_EQ(this->relationShipMap.get("7"),relationMapToAssert.get("7"));
    ASSERT_EQ(this->relationShipMap.get("13"),relationMapToAssert.get("13"));
}

TEST_F(TableUtilTest,testInsertAllForeignKeyToTable){
    HashMap<string,RelationShip*> relationMapToAssert = TableUtil::getOneToOneRelationShips(this->relationShipMap);
    ASSERT_EQ(0,relationMapToAssert.size());
    this->connectorMap.get("8")->setName(RelationType::One);
    this->connectorMap.get("9")->setName(RelationType::One);
    relationMapToAssert = TableUtil::getOneToOneRelationShips(this->relationShipMap);
    ASSERT_EQ(1,relationMapToAssert.size());
    ASSERT_EQ(this->relationShipMap.get("7"),relationMapToAssert.get("7"));
    this->connectorMap.get("17")->setName(RelationType::One);
    this->connectorMap.get("18")->setName(RelationType::One);
    relationMapToAssert = TableUtil::getOneToOneRelationShips(this->relationShipMap);
    ASSERT_EQ(2,relationMapToAssert.size());
    ASSERT_EQ(this->relationShipMap.get("7"),relationMapToAssert.get("7"));
    ASSERT_EQ(this->relationShipMap.get("13"),relationMapToAssert.get("13"));
    
    TableUtil::insertAllEntitiesToTable(this->tableManager,this->entityMap);

    for each(RelationShip* relationShip in relationMapToAssert){
        TableUtil::insertAllForeignKeyToTable(this->tableManager,relationShip);
    }

    ASSERT_EQ(4,this->tableManager.getAllTables().size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("0")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("2")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("4")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("19")->foreignKeyAttributeMap.size());

    this->tableManager = TableManager();
    TableUtil::insertAllEntitiesToTable(this->tableManager,this->entityMap);

    this->attributeMap.get("1")->setAsPrimaryKey();
    this->attributeMap.get("3")->setAsPrimaryKey();
    this->attributeMap.get("10")->setAsPrimaryKey();
    this->attributeMap.get("11")->setAsPrimaryKey();

    for each(RelationShip* relationShip in relationMapToAssert){
        TableUtil::insertAllForeignKeyToTable(this->tableManager,relationShip);
    }

    ASSERT_EQ(4,this->tableManager.getAllTables().size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("0")->foreignKeyAttributeMap.size());
    ASSERT_EQ(2,this->tableManager.getAllTables().get("2")->foreignKeyAttributeMap.size());
    ASSERT_EQ(2,this->tableManager.getAllTables().get("4")->foreignKeyAttributeMap.size());
    ASSERT_EQ(0,this->tableManager.getAllTables().get("19")->foreignKeyAttributeMap.size());
}