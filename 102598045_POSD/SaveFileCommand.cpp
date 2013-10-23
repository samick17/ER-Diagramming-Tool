#include "SaveFileCommand.h"
#include "ReorderComponentsUtil.h"
#include "ERModelUtil.h"
#include "StringSymbol.h"
#include "OutputFileParser.h"

SaveFileCommand::SaveFileCommand(Presentation* presentation) : Command(presentation){	
}

SaveFileCommand::~SaveFileCommand(){
}

void SaveFileCommand::execute(){	
	this->presentation->logMessage("Please input the file name: ",true);
	
	string filePath = this->presentation->getInput();
	
	ERModel* erModel = this->presentation->getERModel();	

	OutputFileParser outputFileParser;
	outputFileParser.parseModelToFile(filePath,erModel);
}