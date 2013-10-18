#include "FindEntityCommand.h"

FindEntityCommand :: FindEntityCommand(Presentation* presentation) : FindComponentCommand(presentation){	
}

FindEntityCommand::~FindEntityCommand(){
}
/**Non testable function**/
void FindEntityCommand :: execute(){
	FindComponentCommand::execute();
	Component* find = getComponent();
	while(typeid(*find).name() != typeid(Entity).name()){
		this->presentation->logMessage("The node '"+find->getID()+"' is not an entity. Please enter a valid one again.",true);
		FindComponentCommand::execute();
		find = getComponent();
	}
	this->component = find;
}