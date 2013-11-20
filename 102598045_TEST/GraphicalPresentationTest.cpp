#include "GraphicalPresentationTest.h"
#include "ComponentData.h"
#include "ComponentType.h"
#include "StateID.h"
#include "ConnectState.h"

void GraphicalPresentationTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void GraphicalPresentationTest::TearDown(){
    delete this->graphicalPresentation;
    delete this->presentation;
}

TEST_F(GraphicalPresentationTest,testDeleteComponentDataForPreview){
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
    this->graphicalPresentation->componentDataForPreview = new ComponentData(ComponentType::TypeAttribute,StringSymbol::Empty);
    this->graphicalPresentation->deleteComponentDataForPreview();
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
}

TEST_F(GraphicalPresentationTest,testUpdateAllComponentData){
    ASSERT_EQ(0,this->graphicalPresentation->componentDataSet.size());
    this->presentation->addNode(ComponentType::TypeAttribute);
    this->presentation->addNode(ComponentType::TypeEntity);
    this->presentation->addNode(ComponentType::TypeRelationShip);
    this->graphicalPresentation->updateAllComponentData();
    ASSERT_EQ(3,this->graphicalPresentation->componentDataSet.size());
    this->graphicalPresentation->componentDataForPreview = new ComponentData(ComponentType::TypeConnector,"4");
    this->graphicalPresentation->updateAllComponentData();
    ASSERT_EQ(4,this->graphicalPresentation->componentDataSet.size());
}

TEST_F(GraphicalPresentationTest,testAddNode){
    ASSERT_EQ(0,this->presentation->getAllComponents().size());
    this->graphicalPresentation->addNode(ComponentType::TypeAttribute,"test",Point());
    ASSERT_EQ(1,this->presentation->getAllComponents().size());
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
}

TEST_F(GraphicalPresentationTest,testAddConnection){
    //test connect fail: with exception
    Component* sourceComponent = new Attribute("0");
    Component* targetComponent = new Entity("1");
    this->graphicalPresentation->addConnection(sourceComponent,sourceComponent);
    ASSERT_EQ(0,sourceComponent->getAllConnections().size());
    ASSERT_EQ(false,sourceComponent->hasConnectedTo(sourceComponent));
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
    //test connect
    this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
    ASSERT_EQ(true,sourceComponent->hasConnectedTo(targetComponent));
    ASSERT_EQ(true,targetComponent->hasConnectedTo(sourceComponent));
    ASSERT_EQ(1,sourceComponent->getAllConnections().size());
    ASSERT_EQ(1,targetComponent->getAllConnections().size());
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
    //test connect again
    this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
    ASSERT_EQ(1,sourceComponent->getAllConnections().size());
    ASSERT_EQ(1,targetComponent->getAllConnections().size());
    ASSERT_EQ(true,sourceComponent->hasConnectedTo(targetComponent));
    ASSERT_EQ(true,targetComponent->hasConnectedTo(sourceComponent));
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
}

TEST_F(GraphicalPresentationTest,testIsWidgetSelected){
    set<string>& selectedWidgetSet = this->graphicalPresentation->selectedWidgetSet;
    ASSERT_EQ(0,selectedWidgetSet.size());
    string selectedID = "0";
    ASSERT_EQ(false,this->graphicalPresentation->isWidgetSelected(selectedID));
    selectedWidgetSet.insert(selectedID);
    ASSERT_EQ(true,this->graphicalPresentation->isWidgetSelected(selectedID));
}

TEST_F(GraphicalPresentationTest,testSelectWidget){
    set<string>& selectedWidgetSet = this->graphicalPresentation->selectedWidgetSet;
    selectedWidgetSet.insert("1");
    //test last Pressed Component is NULL
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(0,selectedWidgetSet.size());
    //test last Pressed Component not NULL
    Component* attribute = new Attribute("5");
    //test select widget without ctrl pressed
    this->graphicalPresentation->lastPressedComponent = attribute;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(1,selectedWidgetSet.size());
    //ASSERT Find attribute's ID
    ASSERT_NE(selectedWidgetSet.end(),selectedWidgetSet.find(attribute->getID()));
    //test select widget again without ctrl pressed
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(0,selectedWidgetSet.size());
    //test select widget with ctrl pressed
    this->graphicalPresentation->isCtrlPressed = true;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(1,selectedWidgetSet.size());
    ASSERT_NE(selectedWidgetSet.end(),selectedWidgetSet.find(attribute->getID()));
    Component* entity = new Entity("7");
    this->graphicalPresentation->lastPressedComponent = entity;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(2,selectedWidgetSet.size());
    ASSERT_NE(selectedWidgetSet.end(),selectedWidgetSet.find(entity->getID()));
    delete attribute;
    delete entity;
}

TEST_F(GraphicalPresentationTest,testSelectLastPressedWidget){
    set<string>& selectedWidgetSet = this->graphicalPresentation->selectedWidgetSet;
    Component* connector = new Connector("12");
    this->graphicalPresentation->selectLastPressedWidget();
    ASSERT_EQ(0,selectedWidgetSet.size());
    this->graphicalPresentation->lastPressedComponent = connector;
    this->graphicalPresentation->selectLastPressedWidget();
    ASSERT_EQ(1,selectedWidgetSet.size());
    this->graphicalPresentation->selectLastPressedWidget();
    ASSERT_EQ(1,selectedWidgetSet.size());
    delete connector;
}

TEST_F(GraphicalPresentationTest,testRevertSelectWidget){
    set<string>& selectedWidgetSet = this->graphicalPresentation->selectedWidgetSet;
    string selectWidgetID = "70";
    this->graphicalPresentation->revertSelectWidget(false,selectWidgetID);	
    ASSERT_EQ(1,selectedWidgetSet.size());
    ASSERT_NE(selectedWidgetSet.end(),selectedWidgetSet.find(selectWidgetID));
    this->graphicalPresentation->revertSelectWidget(true,selectWidgetID);
    ASSERT_EQ(0,selectedWidgetSet.size());
    ASSERT_EQ(selectedWidgetSet.end(),selectedWidgetSet.find(selectWidgetID));
}

TEST_F(GraphicalPresentationTest,testMoveSelectedWidget){
    Component* attribute = this->presentation->addNode(ComponentType::TypeAttribute);
    Component* entity = this->presentation->addNode(ComponentType::TypeEntity);
    Component* relationShip = this->presentation->addNode(ComponentType::TypeRelationShip);
    this->presentation->addConnection(entity,attribute);
    Component* connector = this->presentation->getNodesConnector(entity,attribute);

    Point attributePosition = attribute->getRect().getPosition();
    Point entityPosition = entity->getRect().getPosition();
    Point relationShipPosition = relationShip->getRect().getPosition();
    Point connectorPosition = connector->getRect().getPosition();

    this->graphicalPresentation->selectedWidgetSet.insert(attribute->getID());
    this->graphicalPresentation->selectedWidgetSet.insert(entity->getID());
    this->graphicalPresentation->selectedWidgetSet.insert(relationShip->getID());
    this->graphicalPresentation->selectedWidgetSet.insert(connector->getID());
    this->graphicalPresentation->selectedWidgetSet.insert("test");

    Point deltaPosition = Point(120,201);
    this->graphicalPresentation->moveSelectedWidget(deltaPosition);

    ASSERT_EQ(attributePosition+deltaPosition,attribute->getRect().getPosition());
    ASSERT_EQ(entityPosition+deltaPosition,entity->getRect().getPosition());
    ASSERT_EQ(relationShipPosition+deltaPosition,relationShip->getRect().getPosition());
}

TEST_F(GraphicalPresentationTest,testUnSelectAll){
    set<string>& selectedWidgetSet = this->graphicalPresentation->selectedWidgetSet;
    selectedWidgetSet.insert("test");
    selectedWidgetSet.insert("7");
    this->graphicalPresentation->unSelectAll();
    ASSERT_EQ(0,selectedWidgetSet.size());
}

TEST_F(GraphicalPresentationTest,testSwitchState){
    this->graphicalPresentation->componentDataForPreview = new ComponentData(ComponentType::TypeConnector,"3");
    this->graphicalPresentation->switchState(StateID::ConnectState);
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
    StateSubject* stateSubject = this->graphicalPresentation->getStateSubject();
    ASSERT_EQ(typeid(*stateSubject->getState()).name(),typeid(ConnectState).name());
}

TEST_F(GraphicalPresentationTest,getComponentByComponentData){
    ComponentData* componentData = NULL;
    ASSERT_EQ(NULL,this->graphicalPresentation->getComponentByComponentData(componentData));
    Component* relationShip = this->presentation->addNode(ComponentType::TypeRelationShip);
    ASSERT_EQ(relationShip,this->graphicalPresentation->getComponentByComponentData(relationShip->getComponentData()));

    componentData = new ComponentData(ComponentType::TypeAttribute,"5");
    ASSERT_EQ(NULL,this->graphicalPresentation->getComponentByComponentData(componentData));
}