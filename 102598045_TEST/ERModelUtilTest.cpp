#include "ERModelUtilTest.h"
#include "ERModelUtil.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"

void ERModelUtilTest::SetUp(){
}

void ERModelUtilTest::TearDown(){
}

TEST_F(ERModelUtilTest,testConvertComponentHashMapToTypeHashMap){
	HashMap<string,Component*> componentMap;
	Entity* entity1 = new Entity(ComponentData("0",""));
	Attribute* attribute1 = new Attribute(ComponentData("2",""));
	Connector* connector1 = new Connector(ComponentData("1",""));
	Entity* entity2 = new Entity(ComponentData("24",""));
	RelationShip* relationShip1 = new RelationShip(ComponentData("15",""));
	Connector* connector2 = new Connector(ComponentData("17",""));
	Connector* connector3 = new Connector(ComponentData("6",""));
	RelationShip* relationShip2 = new RelationShip(ComponentData("39",""));
	Attribute* attribute2 = new Attribute(ComponentData("22",""));
	Connector* connector4 = new Connector(ComponentData("48",""));
	Entity* entity3 = new Entity(ComponentData("13",""));

	componentMap.put(entity1->getID(),entity1);
	componentMap.put(attribute1->getID(),attribute1);
	componentMap.put(connector1->getID(),connector1);
	componentMap.put(entity2->getID(),entity2);
	componentMap.put(relationShip1->getID(),relationShip1);
	componentMap.put(connector2->getID(),connector2);
	componentMap.put(connector3->getID(),connector3);
	componentMap.put(relationShip2->getID(),relationShip2);
	componentMap.put(attribute2->getID(),attribute2);
	componentMap.put(connector4->getID(),connector4);
	componentMap.put(entity3->getID(),entity3);
	
	HashMap<string,Component*> componentMapConvert = ERModelUtil::convertComponentHashMapToTypeHashMap<Component>(componentMap);
	ASSERT_EQ(0,componentMapConvert.size());

	HashMap<string,Node*> nodeMapConvert = ERModelUtil::convertComponentHashMapToTypeHashMap<Node>(componentMap);
	ASSERT_EQ(0,nodeMapConvert.size());
	
	HashMap<string,Attribute*> attributeMapConvert = ERModelUtil::convertComponentHashMapToTypeHashMap<Attribute>(componentMap);
	ASSERT_EQ(2,attributeMapConvert.size());
	ASSERT_EQ(attribute1,attributeMapConvert.get("2"));
	ASSERT_EQ(attribute2,attributeMapConvert.get("22"));

	HashMap<string,Entity*> entityMapConvert = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(componentMap);
	ASSERT_EQ(3,entityMapConvert.size());
	ASSERT_EQ(entity1,entityMapConvert.get("0"));
	ASSERT_EQ(entity2,entityMapConvert.get("24"));
	ASSERT_EQ(entity3,entityMapConvert.get("13"));

	HashMap<string,RelationShip*> relaitonShipMapConvert = ERModelUtil::convertComponentHashMapToTypeHashMap<RelationShip>(componentMap);
	ASSERT_EQ(2,relaitonShipMapConvert.size());	
	ASSERT_EQ(relationShip1,relaitonShipMapConvert.get("15"));
	ASSERT_EQ(relationShip2,relaitonShipMapConvert.get("39"));

	HashMap<string,Connector*> connectorMapConvert = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(componentMap);
	ASSERT_EQ(4,connectorMapConvert.size());	
	ASSERT_EQ(connector1,connectorMapConvert.get("1"));
	ASSERT_EQ(connector2,connectorMapConvert.get("17"));
	ASSERT_EQ(connector3,connectorMapConvert.get("6"));
	ASSERT_EQ(connector4,connectorMapConvert.get("48"));

	for each(Component* component in componentMap)
		delete component;	
	componentMap.clear();
}