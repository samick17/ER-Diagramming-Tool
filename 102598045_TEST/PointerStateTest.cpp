#include "PointerStateTest.h"
#include "PointerState.h"
#include "StateID.h"
#include "ComponentType.h"

void PointerStateTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void PointerStateTest::TearDown(){
    delete this->presentation;
    delete this->graphicalPresentation;
}

TEST_F(PointerStateTest,testDoMousePressEvent){
    //test lastPressedComponent is Null
    PointerState pointerState = PointerState(StateID::PointerState,this->graphicalPresentation);
    pointerState.mousePressEvent(Point());
    ASSERT_EQ(true,this->graphicalPresentation->selectedWidgetVector.empty());
    //test lastPressedComponent not NULL && press not selected Widget && not press Ctrl
    Entity* entity = new Entity("0");
    this->graphicalPresentation->lastPressedComponent = entity;
    pointerState.mousePressEvent(Point());
    ASSERT_EQ(1,this->graphicalPresentation->selectedWidgetVector.size());
    ASSERT_EQ("0",this->graphicalPresentation->selectedWidgetVector[0]);

    //test lastPressedComponent not NULL && press selected Widget && not press Ctrl
    pointerState.mousePressEvent(Point());
    ASSERT_EQ(true,this->graphicalPresentation->selectedWidgetVector.empty());

    //test lastPressedComponent not NULL && ctrl
    this->graphicalPresentation->isCtrlPressed = true;
    pointerState.mousePressEvent(Point());
    ASSERT_EQ(1,this->graphicalPresentation->selectedWidgetVector.size());
    ASSERT_EQ("0",this->graphicalPresentation->selectedWidgetVector[0]);

    //test lastPressedComponent not NULL && ctrl && press another
    Attribute* attribute = new Attribute("1");
    this->graphicalPresentation->lastPressedComponent = attribute;
    pointerState.mousePressEvent(Point());
    ASSERT_EQ(2,this->graphicalPresentation->selectedWidgetVector.size());
    ASSERT_EQ("0",this->graphicalPresentation->selectedWidgetVector[0]);
    ASSERT_EQ("1",this->graphicalPresentation->selectedWidgetVector[1]);

    delete entity;
    delete attribute;
}

TEST_F(PointerStateTest,testDoMouseDragEvent){
    //test drag lastPressedWidget && lastPressedWidget is not selected
    PointerState pointerState = PointerState(StateID::PointerState,this->graphicalPresentation);

    this->graphicalPresentation->addNode(ComponentType::TypeEntity,"entity",Point());
    this->graphicalPresentation->lastPressedComponent = this->presentation->getComponentByID("0");
    pointerState.isMousePressed = true;
    Point expectedPosition = Point(-1,1000);
    ASSERT_EQ(Point(),pointerState.currentPosition);
    pointerState.mouseMoveEvent(expectedPosition);
    ASSERT_EQ(expectedPosition,pointerState.deltaPosition);

    ASSERT_EQ(1,this->graphicalPresentation->selectedWidgetVector.size());
    ASSERT_EQ("0",this->graphicalPresentation->selectedWidgetVector[0]);
    ASSERT_EQ(expectedPosition,this->graphicalPresentation->lastPressedComponent->getRect().getCenterPosition());
    //test drag lastPressedWidget && lastPressedWidget is selected
    expectedPosition = Point(5,-100);
    pointerState.mouseMoveEvent(expectedPosition);
    ASSERT_EQ(1,this->graphicalPresentation->selectedWidgetVector.size());
    ASSERT_EQ("0",this->graphicalPresentation->selectedWidgetVector[0]);
    ASSERT_EQ(expectedPosition,this->graphicalPresentation->lastPressedComponent->getRect().getCenterPosition());
}