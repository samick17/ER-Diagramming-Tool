#include "OutputFileParserTest.h"
#include "StringUtil.h"
#include "StringSymbol.h"
#include "ComponentUtil.h"
#include "ERModelUtil.h"

void OutputFileParserTest::SetUp(){
	this->document = new Document("TestDoc");
	Entity* entityCharacter = new Entity(ComponentData("0","Character"));
	Attribute* attributeChar_ID = new Attribute(ComponentData("1","Char_ID"));
	Attribute* attributeJob = new Attribute(ComponentData("2","Job"));
	Attribute* attributeLevel = new Attribute(ComponentData("3","Level"));
	Connector* connector1 = new Connector(ComponentData("4",""));
	Connector* connector2 = new Connector(ComponentData("5",""));
	Connector* connector3 = new Connector(ComponentData("6",""));
	Entity* entityAccount = new Entity(ComponentData("7","Account"));
	RelationShip* relationShipHas1 = new RelationShip(ComponentData("8","Has"));
	Connector* connector4 = new Connector(ComponentData("9",""));
	Connector* connector5 = new Connector(ComponentData("10",""));
	Attribute* attributeAccount_ID = new Attribute(ComponentData("11","Account_ID"));
	Attribute* attributePassword = new Attribute(ComponentData("12","Password"));
	Attribute* attributeSSC_Number = new Attribute(ComponentData("13","SSC_Number"));
	Connector* connector6 = new Connector(ComponentData("14",""));
	Connector* connector7 = new Connector(ComponentData("15",""));
	Connector* connector8 = new Connector(ComponentData("16",""));
	Entity* entityAddress = new Entity(ComponentData("17","Address"));
	Attribute* attributeCountry = new Attribute(ComponentData("18","Country"));
	Attribute* attributeCity = new Attribute(ComponentData("19","City"));
	Attribute* attributePostNumber = new Attribute(ComponentData("20","PostNumber"));	
	RelationShip* relationShipHas2 = new RelationShip(ComponentData("21","Has"));
	Connector* connector9 = new Connector(ComponentData("22",""));
	Connector* connector10 = new Connector(ComponentData("23",""));
	Connector* connector11 = new Connector(ComponentData("24",""));
	Connector* connector12 = new Connector(ComponentData("25",""));
	Connector* connector13 = new Connector(ComponentData("26",""));
	
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

	this->componentMap.put(entityCharacter->getID(),entityCharacter);
	this->componentMap.put(attributeChar_ID->getID(),attributeChar_ID);
	this->componentMap.put(attributeJob->getID(),attributeJob);
	this->componentMap.put(attributeLevel->getID(),attributeLevel);
	this->componentMap.put(connector1->getID(),connector1);
	this->componentMap.put(connector2->getID(),connector2);
	this->componentMap.put(connector3->getID(),connector3);
	this->componentMap.put(entityAccount->getID(),entityAccount);
	this->componentMap.put(relationShipHas1->getID(),relationShipHas1);
	this->componentMap.put(connector4->getID(),connector4);
	this->componentMap.put(connector5->getID(),connector5);
	this->componentMap.put(attributeAccount_ID->getID(),attributeAccount_ID);
	this->componentMap.put(attributePassword->getID(),attributePassword);
	this->componentMap.put(attributeSSC_Number->getID(),attributeSSC_Number);
	this->componentMap.put(connector6->getID(),connector6);
	this->componentMap.put(connector7->getID(),connector7);
	this->componentMap.put(connector8->getID(),connector8);
	this->componentMap.put(entityAddress->getID(),entityAddress);
	this->componentMap.put(attributeCountry->getID(),attributeCountry);
	this->componentMap.put(attributeCity->getID(),attributeCity);
	this->componentMap.put(attributePostNumber->getID(),attributePostNumber);
	this->componentMap.put(relationShipHas2->getID(),relationShipHas2);
	this->componentMap.put(connector9->getID(),connector9);
	this->componentMap.put(connector10->getID(),connector10);
	this->componentMap.put(connector11->getID(),connector11);
	this->componentMap.put(connector12->getID(),connector12);
	this->componentMap.put(connector13->getID(),connector13);
}

void OutputFileParserTest::TearDown(){
	delete this->document;
	for each(Component* component in this->componentMap)
		delete component;	
	this->componentMap.clear();
}

TEST_F(OutputFileParserTest,testWriteAllComponentsToDoc){	
	this->outputFileParser.writeAllComponentsToDoc(*this->document,this->componentMap);
	ASSERT_EQ(28,this->document->rwBuffer.size());

	unsigned int index = 0;
	for each(Component* component in this->componentMap){		
		ASSERT_EQ(component->Component::toString()+StringSymbol::NextLine,this->document->readLine());
		ASSERT_EQ(component->Component::toString()+StringSymbol::NextLine,this->document->rwBuffer[index]);
		index++;
	}
}

TEST_F(OutputFileParserTest,testWriteAllConnectorsToDoc){
	this->outputFileParser.writeAllConnectorsToDoc(*this->document,this->componentMap);
	ASSERT_EQ(14,this->document->rwBuffer.size());

	HashMap<string,Connector*> connectorMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->componentMap);
	unsigned int index = 0;
	for each(Connector* connector in connectorMap){
		ASSERT_EQ(connector->toString()+StringSymbol::NextLine,this->document->readLine());
		ASSERT_EQ(connector->toString()+StringSymbol::NextLine,this->document->rwBuffer[index]);
		index++;
	}
}

TEST_F(OutputFileParserTest,testWriteAllPrimaryKeyToDoc){
	this->outputFileParser.writeAllPrimaryKeyToDoc(*this->document,this->componentMap);
	ASSERT_EQ(1,this->document->rwBuffer.size());

	Entity* entityCharacter = static_cast<Entity*>(this->componentMap.get("0"));
	Entity* entityAccount = static_cast<Entity*>(this->componentMap.get("7"));
	Entity* entityAddress = static_cast<Entity*>(this->componentMap.get("17"));

	vector<string> characterPrimaryKeyVector;
	characterPrimaryKeyVector.push_back("1");
	entityCharacter->setPrimaryKey(characterPrimaryKeyVector);

	delete this->document;
	this->document = new Document("testDoc");

	this->outputFileParser.writeAllPrimaryKeyToDoc(*this->document,this->componentMap);
	ASSERT_EQ(2,this->document->rwBuffer.size());

	HashMap<string,Entity*> entityMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(this->componentMap);
	unsigned int index = 0;
	for each(Entity* entity in entityMap){
		if(entity->toString() == StringSymbol::Empty)
			continue;
		ASSERT_EQ(entity->toString()+StringSymbol::NextLine,this->document->readLine());
		ASSERT_EQ(entity->toString()+StringSymbol::NextLine,this->document->rwBuffer[index]);
		index++;
	}
}