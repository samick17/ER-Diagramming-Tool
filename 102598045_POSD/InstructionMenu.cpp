#include "InstructionMenu.h"
#include "TextPresentation.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "NullPointerException.h"

InstructionMenu::InstructionMenu(){
	this->insertInstructionData(new InstructionData("1","Load ER diagram file",&TextPresentation::openFile));
    this->insertInstructionData(new InstructionData("2","Save ER diagram file",&TextPresentation::saveFile));
    this->insertInstructionData(new InstructionData("3","Add a node",&TextPresentation::addNode));
    this->insertInstructionData(new InstructionData("4","Connect two nodes",&TextPresentation::connectTwoNodes));
    this->insertInstructionData(new InstructionData("5","Display the current diagram",&TextPresentation::displayDiagram));
    this->insertInstructionData(new InstructionData("6","Set a primary key",&TextPresentation::setPrimaryKey));
    this->insertInstructionData(new InstructionData("7","Display the table",&TextPresentation::displayTable));
    this->insertInstructionData(new InstructionData("8","Delete a component",&TextPresentation::deleteComponent));
    this->insertInstructionData(new InstructionData("9","Undo",&TextPresentation::undo));
    this->insertInstructionData(new InstructionData("10","Redo",&TextPresentation::redo));
    this->insertInstructionData(new InstructionData("11","Exit",&TextPresentation::close));
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