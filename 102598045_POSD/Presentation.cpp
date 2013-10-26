#include "Presentation.h"
#include <iostream>
#include "Entity.h"
#include "Connector.h"
#include <iomanip>
#include "ComponentUtil.h"
#include "ERModelUtil.h"
#include "StringUtil.h"
#include "CommandMenu.h"
#include "CommandManager.h"
#include "NullPointerException.h"
#include "EmptyCollectionException.h"
#include "StringSymbol.h"
#include "ComponentType.h"

Presentation::Presentation(ERModel* erModel) : erModel(erModel){
}

Presentation::~Presentation(){
}

ERModel* Presentation::getERModel(){
	return this->erModel;
}

//if alive == false,program will close
void Presentation::close(){
	this->alive = false;
	cout<<"GooBye!"<<endl;
	exit(0);
}

string Presentation::getInput(){
	string input;	
	while(input.length() == 0){
		cout<<">";
		getline(cin,input);		
	}
	return input;
}

void Presentation::displayMenu(){
	this->displayTitle("Commands Menu");
	cout<<" +------------------------------------------------------+"<<endl;	
	CommandMenu commandMenu;
	for each(CommandData* commandData in commandMenu.getCommandDataMap()){
		int length = COMMAND_KEY_WIDTH+commandData->getInfo().size();
		length = MENU_WIDTH-length;
		cout<<"¢x"<<setw(COMMAND_KEY_WIDTH)<<left<<commandData->getKey()+".";
		cout<<right<<commandData->getInfo()<<setw(length)<<"¢x"<<endl;
	}
	cout<<" +------------------------------------------------------+"<<endl;	
}

void Presentation::displayTitle(string title){	
	cout<<"  +----------------------------+"<<endl;
	cout<<" ¢x    "<<title<<setw(TITLE_WIDTH-title.size())<<"¢x"<<endl;
	cout<<"  +----------------------------+"<<endl;
}

void Presentation::displayTable(){
	HashMap<string,Table*> tableMap = erModel->getAllTables();
	if(tableMap.empty())
		throw EmptyCollectionException("Tables");
	
	cout<<" +----------------+--------------------------------------------------"<<endl;
	cout<<" |    Entity      |  Attributes"<<endl;
	cout<<" +----------------+--------------------------------------------------"<<endl;
	for each(Table* table in tableMap){
		string entityName = table->getEntityName();
		int len = TABLE_WIDTH-entityName.size();

		cout<<"   "<<entityName<<setw(len)<<"|";		
		this->displayStringWithComma(" PK(",table->getAllPrimaryKeyAttributesNameVector(),")");		
		this->displayStringWithComma(StringSymbol::Space,table->getAllDefaultKeyAttributesNameVector(),StringSymbol::Empty);		
		this->displayStringWithComma(" FK(",table->getAllForeignKeyAttributesNameVector(),")");	
		cout<<endl;
	}
	cout<<" +----------------+--------------------------------------------------"<<endl;
}

void Presentation::displayComponents(){	
	HashMap<string,Component*> componentMap = erModel->getAllComponents();
	if(componentMap.empty())
		throw EmptyCollectionException(ComponentType::TypeComponent);
	this->displayTitle("Components");
	this->displayComponentSet(componentMap);
}

void Presentation::displayConnections(){	
	HashMap<string,Connector*> connectorMap = erModel->getAllConnectors();
	if(connectorMap.empty())
		throw EmptyCollectionException(ComponentType::TypeConnectorName);
	//convert to vector ordered by id	
	this->displayTitle("Connections");
	cout<<" +----------------------------------------------"<<endl;
	cout<<"    Connectors   |     Node1     |     Node2"<<endl;
	cout<<" +---------------+---------------+--------------"<<endl;
	for each(Connector* connector in connectorMap){	
		cout<<"  "<<setw(COLUMN_WIDTH)<<connector->getID()<<"       ";
		cout<<"|"<<setw(COLUMN_WIDTH)<<connector->getFirstConnectedNode()->getID()<<"       ";
		cout<<"|"<<setw(COLUMN_WIDTH)<<connector->getSecondConnectedNode()->getID()<<endl;		
	}
	cout<<" +----------------------------------------------"<<endl;
}

void Presentation::displayEntities(){
	HashMap<string,Entity*> entityMap = erModel->getAllEntities();
	if(entityMap.empty())
		throw EmptyCollectionException(ComponentType::TypeEntityName);
	this->displayTitle("Entities");
	this->displayComponentSet(ComponentUtil::toComponentHashMap<Entity>(entityMap));
}

void Presentation::displayEntityAttributes(Entity* entity){
	HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
	if(attributeMap.empty())
		throw EmptyCollectionException(ComponentType::TypeAttributeName);
	cout<<"Attributes of the entity '"<<entity->getID()<<"'"<<endl;
	this->displayComponentSet(ComponentUtil::toComponentHashMap<Attribute>(attributeMap));
}

void Presentation::displayStringWithComma(string strStart,vector<string> stringVector,string strEnd){
	if(stringVector.empty())
		return;
	cout<<strStart;
	string stringWithComma = StringUtil::appendWithComma(stringVector);
	cout<<stringWithComma;
	cout<<strEnd;	
}

void Presentation::processCommand(string commandKey){
	Command* command = NULL;
	try{
		CommandMenu commandMenu;
		CommandData* commandData = commandMenu.getCommandDataByKey(commandKey);		
		//get new Command Function From Command Data
		NewCommandFunction newCommandFunction = commandData->getNewCommandFunction();
		//new one Command for Command Manager to Execute
		command = newCommandFunction(this);
		this->executeCommand(command);
	}
	catch(NullPointerException){
		cout<<"wrong command,please input correct command."<<endl;		
	}
	catch(Exception& exception){
		cout<<exception.getMessage()<<endl;		
		delete command;
	}
}

void Presentation::executeCommand(Command* command){
	//display command information & get user input
	string commandInfo = command->getCommandInformation();
	if(commandInfo!= StringSymbol::Empty)
		cout<<commandInfo<<endl;
	
	//execute
	if(command->isUnexecutable()){
		UnexecutableCommand* unexecutableCommand = static_cast<UnexecutableCommand*>(command);
		unexecutableCommand->setupCommand();
		this->commandManager->execute(unexecutableCommand);
	}
	else{		
		command->execute();
		delete command;
	}
}

void Presentation::logMessage(string message,bool nextLine){
	cout<<message;
	if(nextLine)
		cout<<endl;
}

void Presentation::setCommandManager(CommandManager* commandManager){
	this->commandManager = commandManager;
}

CommandManager* Presentation::getCommandManager(){
	return this->commandManager;
}

void Presentation::displayComponentSet(HashMap<string,Component*> componentMap){	
	cout<<" +-----------------------------------------------------"<<endl;
	cout<<"        Type      |       ID       |      Name"<<endl;
	cout<<" +----------------+----------------+-------------------"<<endl;
	for each(Component* component in componentMap){
		cout<<setw(COLUMN_WIDTH)<<component->getType()<<"          ";	
		cout<<"|"<<setw(COLUMN_WIDTH)<<component->getID()<<"        ";	
		cout<<"|  "<<component->getName()<<endl;		
	}
	cout<<" +-----------------------------------------------------"<<endl;
}