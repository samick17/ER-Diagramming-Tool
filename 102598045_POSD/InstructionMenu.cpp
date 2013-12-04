#include "InstructionMenu.h"
#include "NullPointerException.h"
#include "InstructionData.h"
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

InstructionMenu::InstructionMenu(){
    this->insertInstructionData(new InstructionData(ControllerEvent::OpenFile,"Load ER diagram file",newTextInstruction<OpenFileInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::SaveFile,"Save ER diagram file",newTextInstruction<SaveFileInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::AddNode,"Add a node",newTextInstruction<AddNodeInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::ConnectTwoNodes,"Connect two nodes",newTextInstruction<ConnectTwoNodesInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::DisplayDiagram,"Display the current diagram",newTextInstruction<DisplayDiagramInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::SetPrimaryKey,"Set a primary key",newTextInstruction<SetPrimaryKeyInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::DisplayTable,"Display the table",newTextInstruction<DisplayTableInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::DeleteComponent,"Delete a component",newTextInstruction<DeleteComponentInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::Undo,"Undo",newTextInstruction<UndoInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::Redo,"Redo",newTextInstruction<RedoInstruction>));
    this->insertInstructionData(new InstructionData(ControllerEvent::Close,"Exit",newTextInstruction<CloseInstruction>));
}

InstructionMenu::~InstructionMenu(){
    for each(InstructionData* instructionData in this->instructionDataMap)
        delete instructionData;
}

HashMap<string,InstructionData*> InstructionMenu::getInstructionDataMap(){
    return this->instructionDataMap;
}

TextInstruction* InstructionMenu::createInstruction(string instructionKey){
    if(this->instructionDataMap.containsKey(instructionKey)){
        InstructionData* instructionData = this->instructionDataMap.get(instructionKey);
        NewInstructionFunction newInstructionFunction = instructionData->getNewInstructionFunction();
        return newInstructionFunction();
    }
    throw NullPointerException();
}

void InstructionMenu::insertInstructionData(InstructionData* instructionData){
    this->instructionDataMap.put(instructionData->getKey(),instructionData);
}