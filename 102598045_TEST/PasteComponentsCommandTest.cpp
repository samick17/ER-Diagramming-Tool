#include "PasteComponentsCommandTest.h"
#include "PasteComponentsCommand.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "Component.h"
#include "ClipBoard.h"

void PasteComponentsCommandTest::SetUp(){
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

void PasteComponentsCommandTest::TearDown(){
    for each(Component* component in this->componentMap)
        delete component;
    this->componentMap.clear();
}

TEST_F(PasteComponentsCommandTest,testExecute){
    ClipBoard clipBoard;
    int count = 4,pasteCount = 0;
    HashMap<string,Component*> componentMapToPaste;
    Component* attribute = this->componentMap.get("0");
    attribute->setName("name");
    Component* entity = this->componentMap.get("1");
    entity->setName("engineer");
    componentMapToPaste.put(attribute->getID(),attribute);
    componentMapToPaste.put(entity->getID(),entity);
    clipBoard.setData(componentMapToPaste);
    PasteComponentsCommand pasteComponentsCommand(this->componentMap,&clipBoard,&count,pasteCount);

    pasteComponentsCommand.execute();

    ASSERT_EQ(6,this->componentMap.size());
    ASSERT_EQ(true,this->componentMap.containsKey("4"));
    ASSERT_EQ("name",this->componentMap.get("4")->getName());
    ASSERT_EQ(true,this->componentMap.containsKey("5"));
    ASSERT_EQ("engineer",this->componentMap.get("5")->getName());

    ASSERT_EQ(6,count);
}

TEST_F(PasteComponentsCommandTest,testExecutePasteWithConnector){
    ClipBoard clipBoard;
    int count = 4,pasteCount = 0;
    HashMap<string,Component*> componentMapToPaste;
    Component* attribute = this->componentMap.get("0");
    attribute->setName("name");
    Component* entity = this->componentMap.get("1");
    entity->setName("engineer");
    Component* connector = this->componentMap.get("3");
    componentMapToPaste.put(attribute->getID(),attribute);
    componentMapToPaste.put(entity->getID(),entity);
    componentMapToPaste.put(connector->getID(),connector);
    clipBoard.setData(componentMapToPaste);
    PasteComponentsCommand pasteComponentsCommand(this->componentMap,&clipBoard,&count,pasteCount);

    pasteComponentsCommand.execute();

    ASSERT_EQ(7,this->componentMap.size());

    ASSERT_EQ(true,this->componentMap.containsKey("4"));
    ASSERT_EQ("name",this->componentMap.get("4")->getName());
    ASSERT_EQ(true,this->componentMap.containsKey("5"));
    ASSERT_EQ("engineer",this->componentMap.get("5")->getName());
    ASSERT_EQ(true,this->componentMap.containsKey("6"));

    ASSERT_EQ(7,count);
}

TEST_F(PasteComponentsCommandTest,testExecutePasteNodeAndConnector){
    ClipBoard clipBoard;
    int count = 4,pasteCount = 0;
    HashMap<string,Component*> componentMapToPaste;
    Component* attribute = this->componentMap.get("0");
    attribute->setName("name");
    Component* connector = this->componentMap.get("3");
    componentMapToPaste.put(attribute->getID(),attribute);
    componentMapToPaste.put(connector->getID(),connector);
    clipBoard.setData(componentMapToPaste);
    PasteComponentsCommand pasteComponentsCommand(this->componentMap,&clipBoard,&count,pasteCount);

    pasteComponentsCommand.execute();

    ASSERT_EQ(5,this->componentMap.size());

    ASSERT_EQ(true,this->componentMap.containsKey("4"));
    ASSERT_EQ("name",this->componentMap.get("4")->getName());

    ASSERT_EQ(5,count);
}

TEST_F(PasteComponentsCommandTest,testUnexecute){
}