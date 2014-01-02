#include "MoveComponentsCommandTest.h"
#include "MoveComponentsCommand.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "Component.h"

void MoveComponentsCommandTest::SetUp(){
    Component* attribute = new Attribute("0");
    attribute->setPosition(Point(50,90));
    Component* entity = new Entity("1");
    entity->setPosition(Point(0,0));
    Component* relationShip = new RelationShip("2");
    relationShip->setPosition(Point(-100,30));
    Component* connector = new Connector("3");
    attribute->connectTo(connector);
    entity->connectTo(connector);
    connector->connectTo(attribute);
    connector->connectTo(entity);

    componentMap.put(attribute->getID(),attribute);
    componentMap.put(entity->getID(),entity);
    componentMap.put(relationShip->getID(),relationShip);
    componentMap.put(connector->getID(),connector);
}

void MoveComponentsCommandTest::TearDown(){
    for each(Component* component in this->componentMap)
        delete component;
    this->componentMap.clear();
}

TEST_F(MoveComponentsCommandTest,testExecute){
    Point mousePressPosition = Point(10,50);
    Point mouseReleasePosition = Point(-100,80);
    Point deltaPosition = mouseReleasePosition - mousePressPosition;
    MoveComponentsCommand moveComponentsCommand(this->componentMap,mousePressPosition,mouseReleasePosition);

    moveComponentsCommand.execute();

    ASSERT_EQ(Point(50,90)+deltaPosition,this->componentMap.get("0")->getPosition());
    ASSERT_EQ(Point(0,0)+deltaPosition,this->componentMap.get("1")->getPosition());
    ASSERT_EQ(Point(-100,30)+deltaPosition,this->componentMap.get("2")->getPosition());
}

TEST_F(MoveComponentsCommandTest,testUnexecute){
    Point mousePressPosition = Point(200,10);
    Point mouseReleasePosition = Point(-150,120);
    Point deltaPosition = mouseReleasePosition - mousePressPosition;

    MoveComponentsCommand moveComponentsCommand(this->componentMap,mousePressPosition,mouseReleasePosition);

    for each(Component* component in this->componentMap){
        Point position = component->getPosition();
        component->setPosition(position+deltaPosition);
    }

    moveComponentsCommand.executionFlag = true;
    moveComponentsCommand.unExecute();

    ASSERT_EQ(Point(50,90),this->componentMap.get("0")->getPosition());
    ASSERT_EQ(Point(0,0),this->componentMap.get("1")->getPosition());
    ASSERT_EQ(Point(-100,30),this->componentMap.get("2")->getPosition());
}