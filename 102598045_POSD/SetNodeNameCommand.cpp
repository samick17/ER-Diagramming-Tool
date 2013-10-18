#include "SetNodeNameCommand.h"

SetNodeNameCommand::SetNodeNameCommand(Presentation* presentation,Component* node) : Command(presentation),node(node){
}

SetNodeNameCommand::~SetNodeNameCommand(){	
}
/**Non testable function**/
void SetNodeNameCommand::execute(){
	this->presentation->logMessage("Enter the name of this node:",true);	
	string input = this->presentation->getInput();
	//node name out of range
	while(input.size() >= TABLE_WIDTH){
		this->presentation->logMessage("The name you entered is too long,please enter a concise one again.",true);		
		input = this->presentation->getInput();
	}

	this->node->setName(input);	
	this->presentation->logMessage("A node ["+this->node->getClassName()+"] has been added. ID: "+this->node->getID()+",Name: "+this->node->getName(),true);	
}