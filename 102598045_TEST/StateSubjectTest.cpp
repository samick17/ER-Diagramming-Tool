#include "StateSubjectTest.h"
#include "StateID.h"
#include "ERModel.h"
#include "GraphicalPresentation.h"
#include "AddNodeState.h"
#include "ConnectState.h"
#include "PointerState.h"

void StateSubjectTest::SetUp(){
    ASSERT_EQ(NULL,this->stateSubject.state);
}

void StateSubjectTest::TearDown(){
}

TEST_F(StateSubjectTest,testSwitchState){
    ERModel erModel;
    Presentation presentation = Presentation(&erModel);
    GraphicalPresentation graphicalPresentation = GraphicalPresentation(&presentation);

    this->stateSubject.switchState(StateID::AddAttributeState,&graphicalPresentation);
    ASSERT_EQ(typeid(AddNodeState).name(),typeid(*this->stateSubject.state).name());
    this->stateSubject.switchState(StateID::AddEntityState,&graphicalPresentation);
    ASSERT_EQ(typeid(AddNodeState).name(),typeid(*this->stateSubject.state).name());
    this->stateSubject.switchState(StateID::AddRelationShipState,&graphicalPresentation);
    ASSERT_EQ(typeid(AddNodeState).name(),typeid(*this->stateSubject.state).name());
    this->stateSubject.switchState(StateID::ConnectState,&graphicalPresentation);
    ASSERT_EQ(typeid(ConnectState).name(),typeid(*this->stateSubject.state).name());
    this->stateSubject.switchState(StateID::PointerState,&graphicalPresentation);
    ASSERT_EQ(typeid(PointerState).name(),typeid(*this->stateSubject.state).name());
}

TEST_F(StateSubjectTest,testDeleteState){
    this->stateSubject.deleteState();
    ASSERT_EQ(NULL,this->stateSubject.state);

    ERModel erModel;
    Presentation presentation = Presentation(&erModel);
    GraphicalPresentation graphicalPresentation = GraphicalPresentation(&presentation);
    this->stateSubject.state = new AddNodeState(StateID::AddAttributeState,&graphicalPresentation);
    this->stateSubject.deleteState();
    ASSERT_EQ(NULL,this->stateSubject.state);
}