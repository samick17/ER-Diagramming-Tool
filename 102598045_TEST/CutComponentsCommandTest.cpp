#include "CutComponentsCommandTest.h"
#include "CutComponentsCommand.h"
#include "DeleteMultiComponentCommand.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "Component.h"
#include "ClipBoard.h"

void CutComponentsCommandTest::SetUp(){
    Component* attribute = new Attribute("0");
    Component* entity = new Entity("1");
    Component* relationShip = new RelationShip("2");
    Component* connector = new Connector("3");
    attribute->connectTo(connector);
    entity->connectTo(connector);
    connector->connectTo(attribute);
    connector->connectTo(entity);

    this->componentMap.put(attribute->getID(),attribute);
    this->componentMap.put(entity->getID(),entity);
    this->componentMap.put(relationShip->getID(),relationShip);
    this->componentMap.put(connector->getID(),connector);
}

void CutComponentsCommandTest::TearDown(){
    for each(Component* component in this->componentMap){
        delete component;
    }
    this->componentMap.clear();
}

TEST_F(CutComponentsCommandTest,testExecute){
    ClipBoard clipBoard;
    HashMap<string,Component*> componentToCut;
    componentToCut.put("3",this->componentMap.get("3"));
    CutComponentsCommand cutComponentsCommand(this->componentMap,&clipBoard,componentToCut);
    cutComponentsCommand.execute();
    ASSERT_EQ(0,clipBoard.getData().size());
    ASSERT_EQ(false,this->componentMap.containsKey("3"));
}

TEST_F(CutComponentsCommandTest,testExecuteCutConnectorWithOneNode){
    ClipBoard clipBoard;
    HashMap<string,Component*> componentToCut;
    Component* connector = this->componentMap.get("3");
    Component* attribute = this->componentMap.get("0");
    componentToCut.put(connector->getID(),connector);
    componentToCut.put(attribute->getID(),attribute);
    CutComponentsCommand cutComponentsCommand(this->componentMap,&clipBoard,componentToCut);
    cutComponentsCommand.execute();

    ASSERT_EQ(2,this->componentMap.size());
    ASSERT_EQ(true,this->componentMap.containsKey("1"));
    ASSERT_EQ(true,this->componentMap.containsKey("2"));
    ASSERT_EQ(1,clipBoard.componentMap.size());
}

TEST_F(CutComponentsCommandTest,testUnexecute){
    ClipBoard clipBoard;
    HashMap<string,Component*> componentToCut;
    componentToCut.put("3",this->componentMap.get("3"));
    CutComponentsCommand cutComponentsCommand(this->componentMap,&clipBoard,componentToCut);
    cutComponentsCommand.clipBoard->setData(componentToCut);
    cutComponentsCommand.deleteMultiComponentCommand->execute();
    ASSERT_EQ(0,clipBoard.getData().size());
}