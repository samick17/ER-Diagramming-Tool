#include "StateFactoryTest.h"
#include "StateID.h"
#include "ERModel.h"
#include "GraphicalPresentation.h"
#include "AddNodeState.h"
#include "PointerState.h"
#include "ConnectState.h"
#include "SetPrimaryKeyState.h"

void StateFactoryTest::SetUp(){
}

void StateFactoryTest::TearDown(){
}

TEST_F(StateFactoryTest,testCreateState){
    ERModel erModel;
    Presentation presentation = Presentation(&erModel);
    GraphicalPresentation graphicalPresentation = GraphicalPresentation(&presentation);

    State* state = this->stateFactory.createState(StateID::AddAttributeState,&graphicalPresentation);
    ASSERT_EQ(typeid(AddNodeState).name(),typeid(*state).name());
    delete state;
    state = this->stateFactory.createState(StateID::AddEntityState,&graphicalPresentation);
    ASSERT_EQ(typeid(AddNodeState).name(),typeid(*state).name());
    delete state;
    state = this->stateFactory.createState(StateID::AddRelationShipState,&graphicalPresentation);
    ASSERT_EQ(typeid(AddNodeState).name(),typeid(*state).name());
    delete state;
    state = this->stateFactory.createState(StateID::ConnectState,&graphicalPresentation);
    ASSERT_EQ(typeid(ConnectState).name(),typeid(*state).name());
    delete state;
    state = this->stateFactory.createState(StateID::PointerState,&graphicalPresentation);
    ASSERT_EQ(typeid(PointerState).name(),typeid(*state).name());
    delete state;
    state = this->stateFactory.createState(StateID::SetPrimaryKeyState,&graphicalPresentation);
    ASSERT_EQ(typeid(SetPrimaryKeyState).name(),typeid(*state).name());
    delete state;
}