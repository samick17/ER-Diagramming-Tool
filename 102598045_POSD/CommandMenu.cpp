#include "CommandMenu.h"
#include "TextPresentation.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "NullPointerException.h"

CommandMenu::CommandMenu(){
	this->insertCommandData(new CommandData("1","Load ER diagram file",&TextPresentation::openFile));
    this->insertCommandData(new CommandData("2","Save ER diagram file",&TextPresentation::saveFile));
    this->insertCommandData(new CommandData("3","Add a node",&TextPresentation::addNode));
    this->insertCommandData(new CommandData("4","Connect two nodes",&TextPresentation::connectTwoNodes));
    this->insertCommandData(new CommandData("5","Display the current diagram",&TextPresentation::displayDiagram));
    this->insertCommandData(new CommandData("6","Set a primary key",&TextPresentation::setPrimaryKey));
    this->insertCommandData(new CommandData("7","Display the table",&TextPresentation::displayTable));
    this->insertCommandData(new CommandData("8","Delete a component",&TextPresentation::deleteComponent));
    this->insertCommandData(new CommandData("9","Undo",&TextPresentation::undo));
    this->insertCommandData(new CommandData("10","Redo",&TextPresentation::redo));
    this->insertCommandData(new CommandData("11","Exit",&TextPresentation::close));
}

CommandMenu::~CommandMenu(){
    for each(CommandData* commandData in this->commandDataMap)
        delete commandData;
}

HashMap<string,CommandData*> CommandMenu::getCommandDataMap(){
    return this->commandDataMap;
}

CommandData* CommandMenu::getCommandDataByKey(string key){
    if(this->commandDataMap.containsKey(key)){
        return this->commandDataMap.get(key);
    }
    throw NullPointerException();
}

void CommandMenu::insertCommandData(CommandData* commandData){
    this->commandDataMap.put(commandData->getKey(),commandData);
}