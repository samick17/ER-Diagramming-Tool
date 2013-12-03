#include "StateTest.h"
#include "MockState.h"

void StateTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void StateTest::TearDown(){
    delete this->presentation;
    delete this->graphicalPresentation;
}

TEST_F(StateTest,testMousePressEvent){
    MockState mockState;
    mockState.mousePressEvent(Point(300,-100));
    ASSERT_EQ(true,mockState.isMousePressed);
    ASSERT_EQ(Point(300,-100),mockState.currentPosition);
    ASSERT_EQ(Point(),mockState.deltaPosition);
}

TEST_F(StateTest,testMouseMoveEvent){
    MockState mockState;
    Point movePosition = Point(-150,0);
    Point currentPosition = mockState.currentPosition;
    mockState.mouseMoveEvent(movePosition);
    ASSERT_EQ(mockState.deltaPosition,movePosition-currentPosition);
    ASSERT_EQ(true,mockState.isDoMouseMoveEvent);
    ASSERT_EQ(movePosition,mockState.currentPosition);
}

TEST_F(StateTest,testMouseDragEvent){
    MockState mockState;
    mockState.isMousePressed = true;
    Point movePosition = Point(-150,0);
    Point currentPosition = mockState.currentPosition;
    mockState.mouseMoveEvent(movePosition);
    ASSERT_EQ(mockState.deltaPosition,movePosition-currentPosition);
    ASSERT_EQ(true,mockState.isDoMouseDragEvent);
    ASSERT_EQ(movePosition,mockState.currentPosition);
}

TEST_F(StateTest,testMouseReleaseEvent){
    MockState mockState;
    mockState.isMousePressed = true;
    mockState.mouseReleaseEvent(Point());
    ASSERT_EQ(false,mockState.isMousePressed);
    ASSERT_EQ(true,mockState.isDoMouseReleaseEvent);
}