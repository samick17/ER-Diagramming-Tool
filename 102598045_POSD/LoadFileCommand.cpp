#include "LoadFileCommand.h"
#include "CommandManager.h"
#include "ComponentType.h"
#include "DisplayDiagramCommand.h"
#include "FileParser.h"

LoadFileCommand :: LoadFileCommand(Presentation* presentation) : Command(presentation){	
}

LoadFileCommand::~LoadFileCommand(){
}

void LoadFileCommand::setupCommand(){
	this->presentation->logMessage("Please input the file name: ",true);
	this->filePath = this->presentation->getInput();
}

void LoadFileCommand::execute(){
	
	ERModel* erModel = this->presentation->getERModel();
	FileParser fileParser;	
	fileParser.parseFileToModel(this->filePath,erModel);	

	//load file succeed. pop all stack in commandManager
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->popAllStack();
	//display current diagram
	DisplayDiagramCommand displayDiagramCommand(this->presentation);
	displayDiagramCommand.execute();
}

void LoadFileCommand::unExecute(){
}