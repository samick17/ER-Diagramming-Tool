#include "AddNodeCommand.h"
#include "ERModel.h"
#include "SetNodeNameCommand.h"
#include "ComponentType.h"
#include "Exception.h"

using namespace std;

AddNodeCommand::AddNodeCommand(Presentation* presentation) : UnexecutableCommand(presentation){		
	this->node = NULL;
}

AddNodeCommand::~AddNodeCommand(){		
	if(!this->getExecutionFlag()){
		delete this->node;
		this->node = NULL;
	}
}

string AddNodeCommand::getCommandInformation(){
	return "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation";
}

void AddNodeCommand::setupCommand(){
	Component* node = this->getNodeToAdd();
	//set Node Name
	SetNodeNameCommand cmdSetNodeName(this->presentation,node);
	cmdSetNodeName.execute();
	this->node = node;
	//insert this node to ERModel
	ERModel* erModel = this->presentation->getERModel();
	erModel->insertComponent(this->node);
	//display All Compomnents
	this->presentation->displayComponents();
}

void AddNodeCommand::execute(){
	ERModel* erModel = this->presentation->getERModel();

	try{
		erModel->getComponentByID(this->node->getID());
	}
	catch(Exception&){
		erModel->insertComponent(this->node);
	}
	
	this->UnexecutableCommand::execute();
}

void AddNodeCommand::unExecute(){
	//remove node
	ERModel* erModel = this->presentation->getERModel();
	
	erModel->removeComponentByID(this->node->getID());

	this->UnexecutableCommand::unExecute();
}
//get input & return.if doesn't conatins such node,looping getinput
Component* AddNodeCommand::getNodeToAdd(){
	Component* node = NULL;
	while(node == NULL){
		try{
			string input = this->presentation->getInput();
			ERModel* erModel = this->presentation->getERModel();
			node = erModel->addNode(input);
		}
		catch(Exception& exception){
			this->presentation->logMessage(exception.getMessage(),true);
		}
	}
	return node;
}