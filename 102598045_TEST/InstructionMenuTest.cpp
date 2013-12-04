#include "InstructionMenuTest.h"
#include "NullPointerException.h"
#include "ERModel.h"
#include "TextPresentation.h"
#include "AddNodeCommand.h"
#include "InstructionData.h"
#include "DuplicatedKeyException.h"
#include "InstructionMenu.h"
#include "OpenFileInstruction.h"
#include "SaveFileInstruction.h"
#include "AddNodeInstruction.h"
#include "ConnectTwoNodesInstruction.h"
#include "DisplayDiagramInstruction.h"
#include "SetPrimaryKeyInstruction.h"
#include "DisplayTableInstruction.h"
#include "DeleteComponentInstruction.h"
#include "UndoInstruction.h"
#include "RedoInstruction.h"
#include "CloseInstruction.h"
#include "ControllerEvent.h"

void InstructionMenuTest::SetUp(){
    ASSERT_EQ(11,this->instructionMenu.instructionDataMap.size());
}

void InstructionMenuTest::TearDown(){
}

TEST_F(InstructionMenuTest,testCreateInstruction){
    ASSERT_EQ(typeid(OpenFileInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::OpenFile)).name());
    ASSERT_EQ(typeid(SaveFileInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::SaveFile)).name());
    ASSERT_EQ(typeid(AddNodeInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::AddNode)).name());
    ASSERT_EQ(typeid(ConnectTwoNodesInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::ConnectTwoNodes)).name());
    ASSERT_EQ(typeid(DisplayDiagramInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::DisplayDiagram)).name());
    ASSERT_EQ(typeid(SetPrimaryKeyInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::SetPrimaryKey)).name());
    ASSERT_EQ(typeid(DisplayTableInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::DisplayTable)).name());
    ASSERT_EQ(typeid(DeleteComponentInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::DeleteComponent)).name());
    ASSERT_EQ(typeid(UndoInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::Undo)).name());
    ASSERT_EQ(typeid(RedoInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::Redo)).name());
    ASSERT_EQ(typeid(CloseInstruction).name(),typeid(*this->instructionMenu.createInstruction(ControllerEvent::Close)).name());
    ASSERT_THROW(this->instructionMenu.createInstruction("X"),NullPointerException);
}

TEST_F(InstructionMenuTest,testInsertInstructionData){
    ASSERT_EQ(11,this->instructionMenu.instructionDataMap.size());
    InstructionData* openFileInstructionData = new InstructionData("1","Load ER diagram file",InstructionMenu::newTextInstruction<OpenFileInstruction>);
    ASSERT_THROW(this->instructionMenu.insertInstructionData(openFileInstructionData),DuplicatedKeyException);
    InstructionData* findComponentInstructionData = new InstructionData("13","Find Component",InstructionMenu::newTextInstruction<OpenFileInstruction>);
    this->instructionMenu.insertInstructionData(findComponentInstructionData);
    ASSERT_EQ(12,this->instructionMenu.instructionDataMap.size());
}