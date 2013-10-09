#include "SetPrimaryKeyCommand.h"
#include "ERModel.h"
#include "Entity.h"
#include "Attribute.h"
#include "StringUtil.h"
#include "VectorUtil.h"
#include "FindEntityCommand.h"
#include "Exception.h"

SetPrimaryKeyCommand :: SetPrimaryKeyCommand(Presentation* presentation) : Command(presentation){
}

SetPrimaryKeyCommand::~SetPrimaryKeyCommand(){
}

void SetPrimaryKeyCommand :: execute(){
	ERModel* erModel = this->presentation->getERModel();		
	this->presentation->displayEntities();

	FindEntityCommand findEntityCommand(this->presentation);
	findEntityCommand.setInfo("Enter the ID of the entity: ");
	findEntityCommand.execute();

	Component* node = findEntityCommand.getComponent();
	Entity* entity = static_cast<Entity*>(node);	
	this->presentation->displayEntityAttributes(entity);	

	vector<string> attributeIDVector = askPrimaryKeyAttributesID(entity);
	set<string> attributeIDSet = VectorUtil::convertVectorToSet<string>(attributeIDVector);
	entity->setPrimaryKey(attributeIDSet);

	//display Set Primary Key Result
	this->presentation->logMessage("The entity '"+entity->getID()+"' has the primary key ",false);
	this->presentation->displayStringWithComma("(",attributeIDSet,").");
	this->presentation->logMessage("",true);
}

void SetPrimaryKeyCommand::unExecute(){
}
// @return :correct attribute,must has connected with selected entity
vector<string> SetPrimaryKeyCommand::askPrimaryKeyAttributesID(Entity* entity){	
	vector<string> attributeIDSet;
	this->presentation->logMessage("Enter the IDs of the attributes (use a comma to separate two attributes):",true);

	while(true){
		try{
			string input = this->presentation->getInput();

			attributeIDSet = StringUtil::split(input,',');
			for each(string attributeID in attributeIDSet)
			{
				entity->getAttributeByID(attributeID);
			}
			break;
		}
		catch(Exception& exception){
			this->presentation->logMessage(exception.getMessage(),true);
		}
	}	
	return attributeIDSet;
}