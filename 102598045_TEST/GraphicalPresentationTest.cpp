#include "GraphicalPresentationTest.h"
#include "ComponentData.h"
#include "ComponentType.h"
#include "StateID.h"
#include "ConnectState.h"
#include "FileCreator.h"

void GraphicalPresentationTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void GraphicalPresentationTest::TearDown(){
    delete this->graphicalPresentation;
    delete this->presentation;
}

vector<string>::iterator GraphicalPresentationTest::findComponentIDInVector(vector<string>& componentIDVector,string componentID){
    return find(componentIDVector.begin(),componentIDVector.end(),componentID);
}

TEST_F(GraphicalPresentationTest,testDeleteComponentDataForPreview){
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
    this->graphicalPresentation->componentDataForPreview = new ComponentData(ComponentType::TypeAttribute,StringSymbol::Empty);
    this->graphicalPresentation->deleteComponentDataForPreview();
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);
}

TEST_F(GraphicalPresentationTest,testUpdateAllComponentData){
    ASSERT_EQ(0,this->graphicalPresentation->getAllComponentDataMap().size());
    this->presentation->addNode(ComponentType::TypeAttribute);
    this->presentation->addNode(ComponentType::TypeEntity);
    this->presentation->addNode(ComponentType::TypeRelationShip);
    this->graphicalPresentation->updateAllComponentData();
    ASSERT_EQ(3,this->graphicalPresentation->getAllComponentDataMap().size());
    this->graphicalPresentation->componentDataForPreview = new ComponentData(ComponentType::TypeConnector,"4");
    this->graphicalPresentation->updateAllComponentData();
    ASSERT_EQ(3,this->graphicalPresentation->getAllComponentDataMap().size());
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

TEST_F(GraphicalPresentationTest,testOpenFile){
   string filePath = FileCreator::createDefaultFile();

   this->graphicalPresentation->componentDataForPreview = new ComponentData(ComponentType::TypeAttribute,"Preview");

    this->graphicalPresentation->openFile(filePath);

    this->graphicalPresentation->updateAllComponentData();
    ASSERT_EQ(15,this->graphicalPresentation->getAllComponentDataMap().size());
    ASSERT_EQ(NULL,this->graphicalPresentation->componentDataForPreview);

    FileCreator::deleteDefaultFile();
}

TEST_F(GraphicalPresentationTest,testIsWidgetSelected){
    vector<string>& selectedWidgetVector = this->graphicalPresentation->selectedWidgetVector;
    ASSERT_EQ(0,selectedWidgetVector.size());
    string selectedID = "0";
    ASSERT_EQ(false,this->graphicalPresentation->isWidgetSelected(selectedID));
    selectedWidgetVector.push_back(selectedID);
    ASSERT_EQ(true,this->graphicalPresentation->isWidgetSelected(selectedID));
}

TEST_F(GraphicalPresentationTest,testSelectWidget){
    vector<string>& selectedWidgetVector = this->graphicalPresentation->selectedWidgetVector;
    this->graphicalPresentation->isCtrlPressed = false;
    selectedWidgetVector.push_back("1");
    selectedWidgetVector.push_back("3");
    //test lastPressedComponent == NULL
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(0,selectedWidgetVector.size());
    //test lastPressedComponent != NULL
    Component* attribute = new Attribute("5");
    //test select widget without ctrl pressed
    this->graphicalPresentation->lastPressedComponent = attribute;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(1,selectedWidgetVector.size());
    //ASSERT Find attribute's ID
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,attribute->getID()));
    //test select widget again without ctrl pressed
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(0,selectedWidgetVector.size());
    //test select widget with ctrl pressed
    this->graphicalPresentation->isCtrlPressed = true;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(1,selectedWidgetVector.size());
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,attribute->getID()));
    Component* entity = new Entity("7");
    this->graphicalPresentation->lastPressedComponent = entity;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(2,selectedWidgetVector.size());
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,attribute->getID()));
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,entity->getID()));
    //test select again with ctrl pressed
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(1,selectedWidgetVector.size());
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,attribute->getID()));
    //test select widget with ctrl pressed & lastPressedComponent == NULL
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(2,selectedWidgetVector.size());
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,attribute->getID()));
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,entity->getID()));
    this->graphicalPresentation->lastPressedComponent = NULL;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(2,selectedWidgetVector.size());
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,attribute->getID()));
    ASSERT_NE(selectedWidgetVector.end(),this->findComponentIDInVector(selectedWidgetVector,entity->getID()));
    //test without ctrl pressed & lastPressedComponent == NULL, should unselect all
    this->graphicalPresentation->isCtrlPressed = false;
    this->graphicalPresentation->selectWidget();
    ASSERT_EQ(0,selectedWidgetVector.size());
    delete attribute;
    delete entity;
}

TEST_F(GraphicalPresentationTest,testSelectLastPressedWidget){
    vector<string>& selectedWidgetVector = this->graphicalPresentation->selectedWidgetVector;
    Component* connector = new Connector("12");
    this->graphicalPresentation->selectLastPressedWidget();
    ASSERT_EQ(0,selectedWidgetVector.size());
    this->graphicalPresentation->lastPressedComponent = connector;
    this->graphicalPresentation->selectLastPressedWidget();
    ASSERT_EQ(1,selectedWidgetVector.size());
    this->graphicalPresentation->selectLastPressedWidget();
    ASSERT_EQ(1,selectedWidgetVector.size());
    delete connector;
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

    this->graphicalPresentation->selectedWidgetVector.push_back(attribute->getID());
    this->graphicalPresentation->selectedWidgetVector.push_back(entity->getID());
    this->graphicalPresentation->selectedWidgetVector.push_back(relationShip->getID());
    this->graphicalPresentation->selectedWidgetVector.push_back(connector->getID());
    this->graphicalPresentation->selectedWidgetVector.push_back("test");

    Point mousePressPosition = Point(0,0);
    Point mouseReleasePosition = Point(120,201);
    Point deltaPosition = mouseReleasePosition-mousePressPosition;
    this->graphicalPresentation->moveSelectedWidget(mousePressPosition,mouseReleasePosition);

    ASSERT_EQ(attributePosition+deltaPosition,attribute->getRect().getPosition());
    ASSERT_EQ(entityPosition+deltaPosition,entity->getRect().getPosition());
    ASSERT_EQ(relationShipPosition+deltaPosition,relationShip->getRect().getPosition());
}

TEST_F(GraphicalPresentationTest,testUnSelectAll){
    vector<string>& selectedWidgetVector = this->graphicalPresentation->selectedWidgetVector;
    selectedWidgetVector.push_back("test");
    selectedWidgetVector.push_back("7");
    this->graphicalPresentation->unSelectAll();
    ASSERT_EQ(0,selectedWidgetVector.size());
}

TEST_F(GraphicalPresentationTest,testNeedToSetCardinality){
    //test lastAddedConnector is NULL & is need to set Cardinality
    ASSERT_EQ(NULL,this->graphicalPresentation->lastAddedConnector);
    ASSERT_EQ(false,this->graphicalPresentation->needToSetCardinality());

    Component* attribute = this->presentation->addNode(ComponentType::TypeAttribute);
    Component* entity = this->presentation->addNode(ComponentType::TypeEntity);
    Component* relationShip = this->presentation->addNode(ComponentType::TypeRelationShip);
    this->presentation->addConnection(attribute,entity);
    this->presentation->addConnection(entity,relationShip);

    this->graphicalPresentation->lastAddedConnector = dynamic_cast<Connector*>(this->presentation->getComponentByID("3"));
    ASSERT_EQ(false,this->graphicalPresentation->needToSetCardinality());

    this->graphicalPresentation->lastAddedConnector = dynamic_cast<Connector*>(this->presentation->getComponentByID("4"));
    ASSERT_EQ(true,this->graphicalPresentation->needToSetCardinality());
}

TEST_F(GraphicalPresentationTest,testSetCardinality){
    ASSERT_EQ(NULL,this->graphicalPresentation->lastAddedConnector);
    ASSERT_EQ(false,this->graphicalPresentation->setCardinality("1"));
    ASSERT_EQ(false,this->graphicalPresentation->setCardinality("X"));

    Component* attribute = this->presentation->addNode(ComponentType::TypeAttribute);
    Component* entity = this->presentation->addNode(ComponentType::TypeEntity);
    Component* relationShip = this->presentation->addNode(ComponentType::TypeRelationShip);
    this->presentation->addConnection(attribute,entity);
    this->presentation->addConnection(entity,relationShip);

    this->graphicalPresentation->lastAddedConnector = dynamic_cast<Connector*>(this->presentation->getComponentByID("3"));
    ASSERT_EQ(false,this->graphicalPresentation->setCardinality("1"));
    ASSERT_EQ(false,this->graphicalPresentation->setCardinality("N"));

    this->graphicalPresentation->lastAddedConnector = dynamic_cast<Connector*>(this->presentation->getComponentByID("4"));
    ASSERT_EQ(true,this->graphicalPresentation->setCardinality("1"));
    ASSERT_EQ(NULL,this->graphicalPresentation->lastAddedConnector);
    this->graphicalPresentation->lastAddedConnector = dynamic_cast<Connector*>(this->presentation->getComponentByID("4"));
    ASSERT_EQ(true,this->graphicalPresentation->setCardinality("N"));
    ASSERT_EQ(NULL,this->graphicalPresentation->lastAddedConnector);
}


TEST_F(GraphicalPresentationTest,testGetComponentByComponentData){
    ComponentData* componentData = NULL;
    ASSERT_EQ(NULL,this->graphicalPresentation->getComponentByComponentData(componentData));
    Component* relationShip = this->presentation->addNode(ComponentType::TypeRelationShip);
    ASSERT_EQ(relationShip,this->graphicalPresentation->getComponentByComponentData(relationShip->getComponentData()));

    componentData = new ComponentData(ComponentType::TypeAttribute,"5");
    ASSERT_EQ(NULL,this->graphicalPresentation->getComponentByComponentData(componentData));
}