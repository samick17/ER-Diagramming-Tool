#include "InstructionMenu.h"
#include "TextUIPresenter.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "NullPointerException.h"
#include "InstructionData.h"
#include "Entity.h"
#include "StringUtil.h"
#include <iostream>
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

InstructionMenu::InstructionMenu(){
    this->insertInstructionData(new InstructionData("1","Load ER diagram file",newTextInstruction<OpenFileInstruction>));
    this->insertInstructionData(new InstructionData("2","Save ER diagram file",newTextInstruction<SaveFileInstruction>));
    this->insertInstructionData(new InstructionData("3","Add a node",newTextInstruction<AddNodeInstruction>));
    this->insertInstructionData(new InstructionData("4","Connect two nodes",newTextInstruction<ConnectTwoNodesInstruction>));
    this->insertInstructionData(new InstructionData("5","Display the current diagram",newTextInstruction<DisplayDiagramInstruction>));
    this->insertInstructionData(new InstructionData("6","Set a primary key",newTextInstruction<SetPrimaryKeyInstruction>));
    this->insertInstructionData(new InstructionData("7","Display the table",newTextInstruction<DisplayTableInstruction>));
    this->insertInstructionData(new InstructionData("8","Delete a component",newTextInstruction<DeleteComponentInstruction>));
    this->insertInstructionData(new InstructionData("9","Undo",newTextInstruction<UndoInstruction>));
    this->insertInstructionData(new InstructionData("10","Redo",newTextInstruction<RedoInstruction>));
    this->insertInstructionData(new InstructionData("11","Exit",newTextInstruction<CloseInstruction>));
}

InstructionMenu::~InstructionMenu(){
    for each(InstructionData* instructionData in this->instructionDataMap)
        delete instructionData;
}

HashMap<string,InstructionData*> InstructionMenu::getInstructionDataMap(){
    return this->instructionDataMap;
}

InstructionData* InstructionMenu::getInstructionDataByKey(string key){
    if(this->instructionDataMap.containsKey(key)){
        return this->instructionDataMap.get(key);
    }
    throw NullPointerException();
}

void InstructionMenu::insertInstructionData(InstructionData* instructionData){
    this->instructionDataMap.put(instructionData->getKey(),instructionData);
}