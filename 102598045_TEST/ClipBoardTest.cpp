#include "ClipBoardTest.h"
#include "ClipBoard.h"
#include "HashMap.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"

void ClipBoardTest::SetUp(){
}

void ClipBoardTest::TearDown(){
}

TEST_F(ClipBoardTest,testSetData){
    Component* attribute = new Attribute("0");
    Component* entity = new Entity("1");
    Component* relationShip = new RelationShip("2");
    Component* connectorEntityAttribute = new Connector("3");
    Component* connectorEntityRelationShip = new Connector("4");

    connectorEntityAttribute->connectTo(attribute);
    connectorEntityAttribute->connectTo(entity);
    attribute->connectTo(connectorEntityAttribute);
    entity->connectTo(connectorEntityAttribute);
    connectorEntityRelationShip->connectTo(relationShip);
    connectorEntityRelationShip->connectTo(entity);
    relationShip->connectTo(connectorEntityRelationShip);
    entity->connectTo(connectorEntityRelationShip);

    //test copy connected entity & attribute
    ClipBoard clipBoard;

    HashMap<string,Component*> componentMapToCopy;
    componentMapToCopy.put(attribute->getID(),attribute);
    componentMapToCopy.put(entity->getID(),entity);
    componentMapToCopy.put(relationShip->getID(),relationShip);
    componentMapToCopy.put(connectorEntityAttribute->getID(),connectorEntityAttribute);
    componentMapToCopy.put(connectorEntityRelationShip->getID(),connectorEntityRelationShip);

    clipBoard.setData(componentMapToCopy);

    //ASSERT clipBoard
    ASSERT_EQ(5,clipBoard.componentMap.size());
    ASSERT_EQ(true,clipBoard.componentMap.get("3")->getAllConnections().containsKey("0"));
    ASSERT_EQ(true,clipBoard.componentMap.get("3")->getAllConnections().containsKey("1"));
    ASSERT_EQ(true,clipBoard.componentMap.get("0")->getAllConnections().containsKey("3"));
    ASSERT_EQ(true,clipBoard.componentMap.get("1")->getAllConnections().containsKey("3"));
    ASSERT_EQ(true,clipBoard.componentMap.get("4")->getAllConnections().containsKey("2"));
    ASSERT_EQ(true,clipBoard.componentMap.get("4")->getAllConnections().containsKey("1"));
    ASSERT_EQ(true,clipBoard.componentMap.get("2")->getAllConnections().containsKey("4"));
    ASSERT_EQ(true,clipBoard.componentMap.get("1")->getAllConnections().containsKey("4"));

    componentMapToCopy.clear();
    componentMapToCopy.put(attribute->getID(),attribute);
    componentMapToCopy.put(connectorEntityAttribute->getID(),connectorEntityAttribute);

    clipBoard.setData(componentMapToCopy);

    //ASSERT clipBoard
    ASSERT_EQ(1,clipBoard.componentMap.size());
    ASSERT_EQ(true,clipBoard.componentMap.containsKey("0"));

    for each(Component* component in componentMapToCopy)
        delete component;
}

TEST_F(ClipBoardTest,testGetData){
    ClipBoard clipBoard1;

    Component* attribute = new Attribute("0");
    Component* entity = new Entity("1");
    Component* relationShip = new RelationShip("2");
    Component* connectorEntityAttribute = new Connector("3");
    Component* connectorEntityRelationShip = new Connector("4");

    connectorEntityAttribute->connectTo(attribute);
    connectorEntityAttribute->connectTo(entity);
    attribute->connectTo(connectorEntityAttribute);
    entity->connectTo(connectorEntityAttribute);
    connectorEntityRelationShip->connectTo(relationShip);
    connectorEntityRelationShip->connectTo(entity);
    relationShip->connectTo(connectorEntityRelationShip);
    entity->connectTo(connectorEntityRelationShip);

    HashMap<string,Component*> componentMapToCopy;
    componentMapToCopy.put(attribute->getID(),attribute);
    componentMapToCopy.put(entity->getID(),entity);
    componentMapToCopy.put(relationShip->getID(),relationShip);
    componentMapToCopy.put(connectorEntityAttribute->getID(),connectorEntityAttribute);
    componentMapToCopy.put(connectorEntityRelationShip->getID(),connectorEntityRelationShip);

    clipBoard1.componentMap = componentMapToCopy;
    HashMap<string,Component*> clonedComponentMap = clipBoard1.getData();

    ASSERT_EQ(5,clonedComponentMap.size());
    ASSERT_EQ(true,clipBoard1.componentMap.get("3")->getAllConnections().containsKey("0"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("3")->getAllConnections().containsKey("1"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("0")->getAllConnections().containsKey("3"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("1")->getAllConnections().containsKey("3"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("4")->getAllConnections().containsKey("2"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("4")->getAllConnections().containsKey("1"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("2")->getAllConnections().containsKey("4"));
    ASSERT_EQ(true,clipBoard1.componentMap.get("1")->getAllConnections().containsKey("4"));

    componentMapToCopy.clear();

    componentMapToCopy.put(attribute->getID(),attribute);
    componentMapToCopy.put(connectorEntityAttribute->getID(),connectorEntityAttribute);

    clipBoard1.componentMap = componentMapToCopy;
    clonedComponentMap = clipBoard1.getData();

    ASSERT_EQ(1,clonedComponentMap.size());
    ASSERT_EQ(true,clonedComponentMap.containsKey("0"));

    delete entity;
    delete relationShip;
    delete connectorEntityRelationShip;
}