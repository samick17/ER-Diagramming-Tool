#include "ConnectStateTest.h"
#include "ConnectState.h"
#include "StateID.h"
#include "ConnectorData.h"
#include "ComponentType.h"
#include "Attribute.h"

void ConnectStateTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void ConnectStateTest::TearDown(){
    delete this->presentation;
    delete this->graphicalPresentation;
}

TEST_F(ConnectStateTest,testDoMousePressEvent){
    ConnectState connectState = ConnectState(StateID::ConnectState,this->graphicalPresentation);
    //ASSERT press nothing
    ASSERT_EQ(NULL,this->graphicalPresentation->getComponentDataForPreview());

    //ASSERT press connector
    Component* attribute = this->presentation->addNode(ComponentType::TypeAttribute);
    Component* entity = this->presentation->addNode(ComponentType::TypeEntity);
    this->presentation->addConnection(attribute,entity);
    this->graphicalPresentation->lastPressedComponent = this->presentation->getComponentByID("2");
    connectState.mousePressEvent(Point());
    ASSERT_EQ(NULL,this->graphicalPresentation->getComponentDataForPreview());

    //ASSERT press node
    this->graphicalPresentation->lastPressedComponent = entity;
    Point mousePressedPosition = Point(100,-1);
    connectState.mousePressEvent(mousePressedPosition);

    ComponentData* componentDataForPreview = this->graphicalPresentation->getComponentDataForPreview();
    ASSERT_EQ(typeid(ConnectorData).name(),typeid(*componentDataForPreview).name());
}

TEST_F(ConnectStateTest,testDoMouseDragEvent){
    Component* attribute = this->presentation->addNode(ComponentType::TypeAttribute);
    Component* entity = this->presentation->addNode(ComponentType::TypeEntity);
    this->presentation->addConnection(attribute,entity);

    this->graphicalPresentation->componentDataForPreview = new ConnectorData(ComponentData(ComponentType::TypeConnector,"test"));
    this->graphicalPresentation->lastPressedComponent = attribute;
    //test drag to null
    ConnectState connectState = ConnectState(StateID::ConnectState,this->graphicalPresentation);
    connectState.isMousePressed = true;
    Point mouseDragPosition = Point(1000,-500);
    connectState.mouseMoveEvent(mouseDragPosition);
    ConnectorData* connectorData = dynamic_cast<ConnectorData*>(this->graphicalPresentation->componentDataForPreview);
    ConnectorData expectedConnectorData = *connectorData;
    expectedConnectorData.setPointPair(attribute->getRect().getMinDistanceToRectPoint(Rect(mouseDragPosition,Size::Zero)));
    
    ASSERT_EQ(expectedConnectorData.getSourcePoint(),connectorData->getSourcePoint());
    ASSERT_EQ(expectedConnectorData.getTargetPoint(),connectorData->getTargetPoint());
    //test drag to connector
    this->graphicalPresentation->lastMovedComponent = this->presentation->getComponentByID("2");
    connectState.mouseMoveEvent(mouseDragPosition);
    expectedConnectorData = *connectorData;
    expectedConnectorData.setPointPair(attribute->getRect().getMinDistanceToRectPoint(Rect(mouseDragPosition,Size::Zero)));

    ASSERT_EQ(expectedConnectorData.getSourcePoint(),connectorData->getSourcePoint());
    ASSERT_EQ(expectedConnectorData.getTargetPoint(),connectorData->getTargetPoint());
    //test drag to entity
    this->graphicalPresentation->lastMovedComponent = entity;
    connectState.mouseMoveEvent(mouseDragPosition);
    expectedConnectorData = *connectorData;
    expectedConnectorData.setPointPair(attribute->getRect().getMinDistanceToRectPoint(entity->getRect()));

    ASSERT_EQ(expectedConnectorData.getSourcePoint(),connectorData->getSourcePoint());
    ASSERT_EQ(expectedConnectorData.getTargetPoint(),connectorData->getTargetPoint());
}