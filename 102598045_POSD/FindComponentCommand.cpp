#include "FindComponentCommand.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"
#include "Exception.h"

FindComponentCommand :: FindComponentCommand(Presentation* presentation) : Command(presentation){	
	this->component = NULL;
	this->info = "";
}

FindComponentCommand::~FindComponentCommand(){
}

void FindComponentCommand::setInfo(string info){
	this->info = info;
}
/**Non testable function**/
void FindComponentCommand :: execute(){
	ERModel* erModel = this->presentation->getERModel();
	//get All Components too check there has components to find
	erModel->getAllComponents();

	string input;
	Component* find = NULL;
	if(this->info != "")
		this->presentation->logMessage(this->info,true);
	while(find == NULL){
		try{
			input = this->presentation->getInput();
			find = erModel->getComponentByID(input);	
		}
		catch(Exception& exception){
			this->presentation->logMessage(exception.getMessage(),true);
		}	
	}
	this->component = find;
}

Component* FindComponentCommand::getComponent(){
	return this->component;
}