#include "DeleteMultiComponentCommandTest.h"
#include "DeleteMultiComponentCommand.h"
#include "DeleteComponentCommand.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "Component.h"

void DeleteMultiComponentCommandTest::SetUp(){
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

void DeleteMultiComponentCommandTest::TearDown(){
    for each(Component* component in this->componentMap)
        delete component;
    this->componentMap.clear();
}

TEST_F(DeleteMultiComponentCommandTest,testExecute){
    HashMap<string,Component*> componentMapToDelete;
    DeleteMultiComponentCommand deleteMultiComponentCommand1(this->componentMap,componentMapToDelete);
    deleteMultiComponentCommand1.execute();

    ASSERT_EQ(4,this->componentMap.size());

    Component* component = this->componentMap.get("2");
    componentMapToDelete.put(component->getID(),component);
    component = this->componentMap.get("3");
    componentMapToDelete.put(component->getID(),component);

    DeleteMultiComponentCommand deleteMultiComponentCommand2(this->componentMap,componentMapToDelete);
    deleteMultiComponentCommand2.execute();

    ASSERT_EQ(2,this->componentMap.size());
}

TEST_F(DeleteMultiComponentCommandTest,testUnexecute){
    HashMap<string,Component*> componentMapToDelete;

    Component* component = this->componentMap.get("2");
    componentMapToDelete.put(component->getID(),component);
    Component* connector = this->componentMap.get("3");
    componentMapToDelete.put(connector->getID(),connector);

    DeleteMultiComponentCommand deleteMultiComponentCommand(componentMap,componentMapToDelete);

    stack<Command*> deleteCommandStack;
    for each(Component* component in componentMapToDelete){
        if(!componentMap.containsValue(component))
            continue;
        Command* command = new DeleteComponentCommand(componentMap,component);
        command->execute();
        deleteCommandStack.push(command);
    }
    deleteMultiComponentCommand.executionFlag = true;
    deleteMultiComponentCommand.deleteCommandStack = deleteCommandStack;

    deleteMultiComponentCommand.unExecute();

    ASSERT_EQ(4,this->componentMap.size());
    ASSERT_EQ(component,this->componentMap.get("2"));
    ASSERT_EQ(connector,this->componentMap.get("3"));
}