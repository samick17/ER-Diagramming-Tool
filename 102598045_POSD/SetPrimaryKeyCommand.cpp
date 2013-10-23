#include "SetPrimaryKeyCommand.h"
#include "ERModel.h"
#include "Entity.h"
#include "Attribute.h"
#include "StringUtil.h"
#include "FindEntityCommand.h"
#include "Exception.h"
#include "StringSymbol.h"
#include "CharSymbol.h"

SetPrimaryKeyCommand::SetPrimaryKeyCommand(Presentation* presentation) : Command(presentation){
}

SetPrimaryKeyCommand::~SetPrimaryKeyCommand(){
}

void SetPrimaryKeyCommand::execute(){
	ERModel* erModel = this->presentation->getERModel();		
	this->presentation->displayEntities();

	FindEntityCommand findEntityCommand(this->presentation);
	findEntityCommand.setInfo("Enter the ID of the entity: ");
	findEntityCommand.execute();

	Component* node = findEntityCommand.getComponent();
	Entity* entity = static_cast<Entity*>(node);
	this->presentation->displayEntityAttributes(entity);

	this->presentation->logMessage("Enter the IDs of the attributes (use a comma to separate two attributes):",true);
	vector<string> attributeIDVector = setEntityAttributesPrimaryKey(entity);	
	//display Set Primary Key Result
	this->presentation->logMessage("The entity '"+entity->getID()+"' has the primary key ",false);
	this->presentation->displayStringWithComma("(",attributeIDVector,").");
	this->presentation->logMessage(StringSymbol::Empty,true);
}

vector<string> SetPrimaryKeyCommand::setEntityAttributesPrimaryKey(Entity* entity){
	vector<string> attributeIDVector;	
	while(true){
		try{
			string input = this->presentation->getInput();
			attributeIDVector = StringUtil::split(input,CharSymbol::Comma);
			entity->setPrimaryKey(attributeIDVector);
			break;
		}
		catch(Exception& exception){
			this->presentation->logMessage(exception.getMessage(),true);
		}
	}
	return  attributeIDVector;
}