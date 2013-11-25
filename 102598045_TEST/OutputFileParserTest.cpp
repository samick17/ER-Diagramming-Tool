#include "OutputFileParserTest.h"
#include "StringUtil.h"
#include "StringSymbol.h"
#include "ComponentUtil.h"
#include "ERModelUtil.h"

void OutputFileParserTest::SetUp(){
    this->document = new Document("TestDoc");
    Entity* entityCharacter = new Entity("0","Character");
    Attribute* attributeChar_ID = new Attribute("1","Char_ID");
    Attribute* attributeJob = new Attribute("2","Job");
    Attribute* attributeLevel = new Attribute("3","Level");
    Connector* connector1 = new Connector("4");
    Connector* connector2 = new Connector("5");
    Connector* connector3 = new Connector("6");
    Entity* entityAccount = new Entity("7","Account");
    RelationShip* relationShipHas1 = new RelationShip("8","Has");
    Connector* connector4 = new Connector("9");
    Connector* connector5 = new Connector("10");
    Attribute* attributeAccount_ID = new Attribute("11","Account_ID");
    Attribute* attributePassword = new Attribute("12","Password");
    Attribute* attributeSSC_Number = new Attribute("13","SSC_Number");
    Connector* connector6 = new Connector("14");
    Connector* connector7 = new Connector("15");
    Connector* connector8 = new Connector("16");
    Entity* entityAddress = new Entity("17","Address");
    Attribute* attributeCountry = new Attribute("18","Country");
    Attribute* attributeCity = new Attribute("19","City");
    Attribute* attributePostNumber = new Attribute("20","PostNumber");
    RelationShip* relationShipHas2 = new RelationShip("21","Has");
    Connector* connector9 = new Connector("22");
    Connector* connector10 = new Connector("23");
    Connector* connector11 = new Connector("24");
    Connector* connector12 = new Connector("25");
    Connector* connector13 = new Connector("26");
    
    ComponentUtil::connectWithEachOther(entityCharacter,attributeChar_ID,connector1);
    ComponentUtil::connectWithEachOther(entityCharacter,attributeJob,connector2);
    ComponentUtil::connectWithEachOther(entityCharacter,attributeLevel,connector3);
    ComponentUtil::connectWithEachOther(entityCharacter,relationShipHas1,connector4);
    ComponentUtil::connectWithEachOther(entityAccount,relationShipHas1,connector5);
    ComponentUtil::connectWithEachOther(entityAccount,attributeAccount_ID,connector6);
    ComponentUtil::connectWithEachOther(entityAccount,attributePassword,connector7);
    ComponentUtil::connectWithEachOther(entityAccount,attributeSSC_Number,connector8);
    ComponentUtil::connectWithEachOther(entityAddress,attributeCountry,connector9);
    ComponentUtil::connectWithEachOther(entityAddress,attributeCity,connector10);
    ComponentUtil::connectWithEachOther(entityAddress,attributePostNumber,connector11);
    ComponentUtil::connectWithEachOther(entityAccount,relationShipHas2,connector12);
    ComponentUtil::connectWithEachOther(entityAddress,relationShipHas2,connector13);

    this->insertComponentMap(entityCharacter);
    this->insertComponentMap(attributeChar_ID);
    this->insertComponentMap(attributeJob);
    this->insertComponentMap(attributeLevel);
    this->insertComponentMap(connector1);
    this->insertComponentMap(connector2);
    this->insertComponentMap(connector3);
    this->insertComponentMap(entityAccount);
    this->insertComponentMap(relationShipHas1);
    this->insertComponentMap(connector4);
    this->insertComponentMap(connector5);
    this->insertComponentMap(attributeAccount_ID);
    this->insertComponentMap(attributePassword);
    this->insertComponentMap(attributeSSC_Number);
    this->insertComponentMap(connector6);
    this->insertComponentMap(connector7);
    this->insertComponentMap(connector8);
    this->insertComponentMap(entityAddress);
    this->insertComponentMap(attributeCountry);
    this->insertComponentMap(attributeCity);
    this->insertComponentMap(attributePostNumber);
    this->insertComponentMap(relationShipHas2);
    this->insertComponentMap(connector9);
    this->insertComponentMap(connector10);
    this->insertComponentMap(connector11);
    this->insertComponentMap(connector12);
    this->insertComponentMap(connector13);

    this->outputFileParser = new OutputFileParser(this->componentMap);
}

void OutputFileParserTest::TearDown(){
    delete this->document;
    for each(Component* component in this->componentMap)
        delete component;    
    this->componentMap.clear();
    delete this->outputFileParser;
}

void OutputFileParserTest::insertComponentMap(Component* component){
    this->componentMap.put(component->getID(),component);
}

TEST_F(OutputFileParserTest,testWriteAllComponentsToDoc){    
    this->outputFileParser->writeAllComponentsToDoc(*this->document,this->componentMap);
    ASSERT_EQ(28,this->document->rwBuffer.size());

    unsigned int index = 0;
    for each(Component* component in this->componentMap){        
        ASSERT_EQ(this->outputFileParser->serializeComponentToString(component)+StringSymbol::NextLine,this->document->readLine());
        ASSERT_EQ(this->outputFileParser->serializeComponentToString(component)+StringSymbol::NextLine,this->document->rwBuffer[index]);
        index++;
    }
}

TEST_F(OutputFileParserTest,testWriteAllConnectorsToDoc){
    this->outputFileParser->writeAllConnectorsToDoc(*this->document,this->componentMap);
    ASSERT_EQ(14,this->document->rwBuffer.size());

    HashMap<string,Connector*> connectorMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->componentMap);
    unsigned int index = 0;
    for each(Connector* connector in connectorMap){
        ASSERT_EQ(this->outputFileParser->serializeConnectorToString(connector)+StringSymbol::NextLine,this->document->readLine());
        ASSERT_EQ(this->outputFileParser->serializeConnectorToString(connector)+StringSymbol::NextLine,this->document->rwBuffer[index]);
        index++;
    }
}

TEST_F(OutputFileParserTest,testWriteAllPrimaryKeyToDoc){
    this->outputFileParser->writeAllPrimaryKeyToDoc(*this->document,this->componentMap);
    ASSERT_EQ(1,this->document->rwBuffer.size());

    Entity* entityCharacter = static_cast<Entity*>(this->componentMap.get("0"));
    Entity* entityAccount = static_cast<Entity*>(this->componentMap.get("7"));
    Entity* entityAddress = static_cast<Entity*>(this->componentMap.get("17"));

    entityCharacter->setPrimaryKey("1");

    delete this->document;
    this->document = new Document("testDoc");

    this->outputFileParser->writeAllPrimaryKeyToDoc(*this->document,this->componentMap);
    ASSERT_EQ(2,this->document->rwBuffer.size());

    HashMap<string,Entity*> entityMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(this->componentMap);
    unsigned int index = 0;
    for each(Entity* entity in entityMap){
        if(this->outputFileParser->serializeEntityToString(entity) == StringSymbol::Empty)
            continue;
        ASSERT_EQ(this->outputFileParser->serializeEntityToString(entity)+StringSymbol::NextLine,this->document->readLine());
        ASSERT_EQ(this->outputFileParser->serializeEntityToString(entity)+StringSymbol::NextLine,this->document->rwBuffer[index]);
        index++;
    }
}

TEST_F(OutputFileParserTest,testSerializeComponentToString){
    ASSERT_EQ("E, Character",this->outputFileParser->serializeComponentToString(this->componentMap.get("0")));
    ASSERT_EQ("A, Level",this->outputFileParser->serializeComponentToString(this->componentMap.get("3")));
    ASSERT_EQ("C",this->outputFileParser->serializeComponentToString(this->componentMap.get("10")));
    ASSERT_EQ("R, Has",this->outputFileParser->serializeComponentToString(this->componentMap.get("21")));
    ASSERT_EQ("C",this->outputFileParser->serializeComponentToString(this->componentMap.get("25")));
}

TEST_F(OutputFileParserTest,testSerializeEntityToString){
    ASSERT_EQ("",this->outputFileParser->serializeEntityToString(static_cast<Entity*>(this->componentMap.get("0"))));
    ASSERT_EQ("",this->outputFileParser->serializeEntityToString(static_cast<Entity*>(this->componentMap.get("7"))));
    ASSERT_EQ("",this->outputFileParser->serializeEntityToString(static_cast<Entity*>(this->componentMap.get("17"))));
}

TEST_F(OutputFileParserTest,testSerializeConnectorToString){
    ASSERT_EQ("4 0,1",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("4"))));
    ASSERT_EQ("5 0,2",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("5"))));
    ASSERT_EQ("6 0,3",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("6"))));
    ASSERT_EQ("9 0,8",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("9"))));
    ASSERT_EQ("10 7,8",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("10"))));
    ASSERT_EQ("14 7,11",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("14"))));
    ASSERT_EQ("15 7,12",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("15"))));
    ASSERT_EQ("16 7,13",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("16"))));
    ASSERT_EQ("22 17,18",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("22"))));
    ASSERT_EQ("23 17,19",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("23"))));
    ASSERT_EQ("24 17,20",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("24"))));
    ASSERT_EQ("25 7,21",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("25"))));
    ASSERT_EQ("26 17,21",this->outputFileParser->serializeConnectorToString(static_cast<Connector*>(this->componentMap.get("26"))));
}