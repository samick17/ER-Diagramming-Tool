#include "OpenFileCommand.h"
#include "CommandManager.h"
#include "ComponentType.h"
#include "DisplayDiagramCommand.h"
#include "InputFileParser.h"

OpenFileCommand::OpenFileCommand(Presentation* presentation) : Command(presentation){	
}

OpenFileCommand::~OpenFileCommand(){
}

/**Non testable function**/
void OpenFileCommand::execute(){
	this->presentation->logMessage("Please input the file name: ",true);
	this->filePath = this->presentation->getInput();
	this->presentation->openFile(this->filePath);
}