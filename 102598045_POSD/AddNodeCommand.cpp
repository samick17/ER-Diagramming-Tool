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
	if(!this->getExecutionFlag())
		delete this->node;
}

void AddNodeCommand::execute(){
	if(this->node != NULL){			
		ERModel* erModel = this->presentation->getERModel();
		//add to erModel
		erModel->addComponent(this->node);		
	}
	else 	
		this->doAddNode();
	
	this->UnexecutableCommand::execute();
}

void AddNodeCommand::unExecute(){
	//remove node
	ERModel* erModel = this->presentation->getERModel();
	
	erModel->removeComponentByID(this->node->getID());

	this->UnexecutableCommand::unExecute();
}

void AddNodeCommand::doAddNode(){
	this->presentation->logMessage("What kind of node do you want to add? ",true);
	this->presentation->logMessage("[A]Attribute [E]Entity [R]Relation",true);
	
	Component* node = this->getNodeToAdd();

	SetNodeNameCommand cmdSetNodeName(this->presentation,node);
	cmdSetNodeName.execute();
	this->node = node;

	this->presentation->displayComponents();
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