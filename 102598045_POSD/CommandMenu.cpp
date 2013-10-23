#include "CommandMenu.h"
#include "LoadFileCommand.h"
#include "SaveFileCommand.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DisplayDiagramCommand.h"
#include "SetPrimaryKeyCommand.h"
#include "DisplayTableCommand.h"
#include "DeleteComponentCommand.h"
#include "UndoCommand.h"
#include "RedoCommand.h"
#include "ExitCommand.h"
#include "NullPointerException.h"

CommandMenu::CommandMenu(){	
	this->insertCommandData(new CommandData("1","Load ER diagram file",newCommand<LoadFileCommand>));
	this->insertCommandData(new CommandData("2","Save ER diagram file",newCommand<SaveFileCommand>));
	this->insertCommandData(new CommandData("3","Add a node",newCommand<AddNodeCommand>));
	this->insertCommandData(new CommandData("4","Connect two nodes",newCommand<ConnectNodeCommand>));
	this->insertCommandData(new CommandData("5","Display the current diagram",newCommand<DisplayDiagramCommand>));
	this->insertCommandData(new CommandData("6","Set a primary key",newCommand<SetPrimaryKeyCommand>));
	this->insertCommandData(new CommandData("7","Display the table",newCommand<DisplayTableCommand>));
	this->insertCommandData(new CommandData("8","Delete a component",newCommand<DeleteComponentCommand>));
	this->insertCommandData(new CommandData("9","Undo",newCommand<UndoCommand>));
	this->insertCommandData(new CommandData("10","Redo",newCommand<RedoCommand>));
	this->insertCommandData(new CommandData("11","Exit",newCommand<ExitCommand>));
}

CommandMenu::~CommandMenu(){
	for each (CommandData* commandData in this->commandDataMap)
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