#include "SetPrimaryKeyStateTest.h"
#include "GraphicalPresentation.h"
#include "ComponentType.h"
#include "SetPrimaryKeyState.h"
#include "StateID.h"

void SetPrimaryKeyStateTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void SetPrimaryKeyStateTest::TearDown(){
    delete this->presentation;
    delete this->graphicalPresentation;
}

TEST_F(SetPrimaryKeyStateTest,testDoMousePressEvent){
    //test not connected attribute
    this->graphicalPresentation->addNode(ComponentType::TypeEntity,"entity",Point());
    this->graphicalPresentation->addNode(ComponentType::TypeAttribute,"attribute",Point());
    SetPrimaryKeyState setPrimaryKeyState = SetPrimaryKeyState(StateID::SetPrimaryKeyState,this->graphicalPresentation);
    Attribute* attribute = dynamic_cast<Attribute*>(this->presentation->getComponentByID("1"));

    this->graphicalPresentation->lastPressedComponent = attribute;
    setPrimaryKeyState.mousePressEvent(Point());
    ASSERT_EQ(false,attribute->isPrimaryKey());
    //press again
    this->graphicalPresentation->lastPressedComponent = attribute;
    setPrimaryKeyState.mousePressEvent(Point());
    ASSERT_EQ(false,attribute->isPrimaryKey());
    //happy path
    this->graphicalPresentation->addConnection(this->presentation->getComponentByID("0"),this->presentation->getComponentByID("1"));
    setPrimaryKeyState.mousePressEvent(Point());
    ASSERT_EQ(true,attribute->isPrimaryKey());
    setPrimaryKeyState.mousePressEvent(Point());
    ASSERT_EQ(false,attribute->isPrimaryKey());
    setPrimaryKeyState.mousePressEvent(Point());
    ASSERT_EQ(true,attribute->isPrimaryKey());
}