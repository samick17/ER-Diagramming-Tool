#include "AddNodeStateTest.h"
#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include "PointerState.h"

void AddNodeStateTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void AddNodeStateTest::TearDown(){
    delete this->presentation;
    delete this->graphicalPresentation;
}

TEST_F(AddNodeStateTest,testOnCreate){
    //ASSERT AddNode-Attribute onCreate
    AddNodeState addNodeState = AddNodeState(StateID::AddAttributeState,this->graphicalPresentation);
    addNodeState.onCreate();
    ASSERT_EQ(ComponentType::TypeAttribute,this->graphicalPresentation->getComponentDataForPreview()->getType());
    //ASSERT AddNode-Entity onCreate
    addNodeState = AddNodeState(StateID::AddEntityState,this->graphicalPresentation);
    addNodeState.onCreate();
    ASSERT_EQ(ComponentType::TypeEntity,this->graphicalPresentation->getComponentDataForPreview()->getType());
    //ASSERT AddNode-RelationShip onCreate
    addNodeState = AddNodeState(StateID::AddRelationShipState,this->graphicalPresentation);
    addNodeState.onCreate();
    ASSERT_EQ(ComponentType::TypeRelationShip,this->graphicalPresentation->getComponentDataForPreview()->getType());
}

TEST_F(AddNodeStateTest,testDoMouseMoveEvent){
    //ASSERT Preview Component's position
    AddNodeState addNodeState = AddNodeState(StateID::AddEntityState,this->graphicalPresentation);
    this->graphicalPresentation->setComponentDataForPreview(new ComponentData(ComponentType::TypeEntity,"test"));

    ComponentData* componentDataForPreview = this->graphicalPresentation->getComponentDataForPreview();
    
    Point movePosition = Point(-1,1);
    addNodeState.mouseMoveEvent(movePosition);
    ASSERT_EQ(movePosition,componentDataForPreview->getRect().getCenterPosition());

    movePosition = Point(1000,1000);
    addNodeState.mouseMoveEvent(movePosition);
    ASSERT_EQ(movePosition,componentDataForPreview->getRect().getCenterPosition());

    movePosition = Point(0,0);
    addNodeState.mouseMoveEvent(movePosition);
    ASSERT_EQ(movePosition,componentDataForPreview->getRect().getCenterPosition());
}

TEST_F(AddNodeStateTest,testDoMouseReleaseEvent){
    AddNodeState addNodeState = AddNodeState(StateID::AddAttributeState,this->graphicalPresentation);
    this->graphicalPresentation->setComponentDataForPreview(new ComponentData(ComponentType::TypeAttribute,"test"));

    ASSERT_EQ(0,this->graphicalPresentation->getAllComponentDataMap().size());
    addNodeState.mouseReleaseEvent(Point(800,-1));
    ASSERT_EQ(1,this->presentation->getAllComponents().size());
    ASSERT_EQ(ComponentType::TypeAttribute,this->presentation->getAllComponents().get("0")->getType());
    ASSERT_EQ(StateID::PointerState,this->graphicalPresentation->getCurrentStateID());
}