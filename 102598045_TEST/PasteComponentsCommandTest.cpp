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
    for each(Component* component in this->componentMap){
        delete component;
    }
    this->componentMap.clear();
}

TEST_F(PasteComponentsCommandTest,testExecute){
    ClipBoard clipBoard;
    int count,pasteCount;
    HashMap<string,Component*> componentToCut;
    PasteComponentsCommand pasteComponentsCommand(this->componentMap,&clipBoard,&count,pasteCount);
}

TEST_F(PasteComponentsCommandTest,testUnexecute){
}