#include "SetCardinalityCommand.h"
#include "StringUtil.h"

SetCardinalityCommand :: SetCardinalityCommand(Presentation* presentation,Component* firstNode,Component* secondNode) : Command(presentation),firstNode(firstNode),secondNode(secondNode){	
}

SetCardinalityCommand::~SetCardinalityCommand(){
}
/**Non testable function**/
void SetCardinalityCommand :: execute(){
	ERModel* erModel = this->presentation->getERModel();
	
	this->presentation->logMessage("Enter the type of the cardinality: ",true);
	this->presentation->logMessage("[0]1 [1]N",true);
	this->presentation->logMessage("The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"'.",true);	
	string input = this->presentation->getInput();

	while(input != "0"){
		this->presentation->logMessage("the cardinality you entered doesn't exist. Please entered a valid one again",true);		
		input = this->presentation->getInput();
	}
	Connector* connection = erModel->getNodesConnector(firstNode,secondNode);
	string relationName = RelationType::OneToOne;
	connection->setName(relationName);

	this->presentation->logMessage("Its cardinality of the relationship is '"+relationName+"'.",true);
}