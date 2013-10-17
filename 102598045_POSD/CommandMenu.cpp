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
	CommandData* commandData[11];
	
	commandData[0] = new CommandData("1","Load ER diagram file",newCommand<LoadFileCommand>);
	commandData[1] = new CommandData("2","Save ER diagram file",newCommand<SaveFileCommand>);
	commandData[2] = new CommandData("3","Add a node",newCommand<AddNodeCommand>);
	commandData[3] = new CommandData("4","Connect two nodes",newCommand<ConnectNodeCommand>);
	commandData[4] = new CommandData("5","Display the current diagram",newCommand<DisplayDiagramCommand>);
	commandData[5] = new CommandData("6","Set a primary key",newCommand<SetPrimaryKeyCommand>);
	commandData[6] = new CommandData("7","Display the table",newCommand<DisplayTableCommand>);
	commandData[7] = new CommandData("8","Delete a component",newCommand<DeleteComponentCommand>);
	commandData[8] = new CommandData("9","Undo",newCommand<UndoCommand>);
	commandData[9] = new CommandData("10","Redo",newCommand<RedoCommand>);
	commandData[10] = new CommandData("11","Exit",newCommand<ExitCommand>);

	for each(CommandData* cmdData in commandData){
		this->insertCommandData(cmdData);
	}
}

CommandMenu::~CommandMenu(){
	for each (CommandDataPair commandDataPair in this->commandDataMap)	{
		delete commandDataPair.second;
	}
	
	this->commandDataMap.clear();
	this->commandDataKeyOrderVector.clear();
}

vector<CommandData*> CommandMenu::getCommandDataVector(){
	vector<CommandData*> commandDataVector;
	for each(string key in commandDataKeyOrderVector)	
		commandDataVector.push_back(this->commandDataMap.find(key)->second);
	
	return commandDataVector;
}

CommandData* CommandMenu::getCommandDataByKey(string key){
	unordered_map<string,CommandData*>::iterator commandDataIterator;
	if((commandDataIterator = this->commandDataMap.find(key)) != this->commandDataMap.end())	
		return commandDataIterator->second;

	throw NullPointerException();
}

void CommandMenu::insertCommandData(CommandData* commandData){
	this->commandDataMap.insert(CommandDataPair(commandData->getKey(),commandData));	
	//in order to keep command order, use a vector to convert commandData key to vector
	this->commandDataKeyOrderVector.push_back(commandData->getKey());
}