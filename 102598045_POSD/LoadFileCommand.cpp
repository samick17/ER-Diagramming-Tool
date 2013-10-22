#include "LoadFileCommand.h"
#include "CommandManager.h"
#include "ComponentType.h"
#include "DisplayDiagramCommand.h"
#include "InputFileParser.h"

LoadFileCommand :: LoadFileCommand(Presentation* presentation) : Command(presentation){	
}

LoadFileCommand::~LoadFileCommand(){
}

/**Non testable function**/
void LoadFileCommand::execute(){
	this->presentation->logMessage("Please input the file name: ",true);
	this->filePath = this->presentation->getInput();
	ERModel* erModel = this->presentation->getERModel();
	InputFileParser inputFileParser;	
	inputFileParser.parseFileToModel(this->filePath,erModel);

	//load file succeed. pop all stack in commandManager
	CommandManager* commandManager = this->presentation->getCommandManager();
	commandManager->popAllStack();
	//display current diagram
	DisplayDiagramCommand displayDiagramCommand(this->presentation);
	displayDiagramCommand.execute();
}