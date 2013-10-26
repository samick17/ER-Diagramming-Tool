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
#include "TextUI.h"
#include "InputFileParser.h"

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

void Presentation::displayTable(){
	HashMap<string,Table*> tableMap = erModel->getAllTables();
	if(tableMap.empty())
		throw EmptyCollectionException("Tables");
	this->textUI->displayTable(tableMap);
}

void Presentation::displayComponents(){	
	HashMap<string,Component*> componentMap = erModel->getAllComponents();
	if(componentMap.empty())
		throw EmptyCollectionException(ComponentType::TypeComponent);
	this->textUI->displayComponents(componentMap);
}

void Presentation::displayConnections(){	
	HashMap<string,Connector*> connectorMap = erModel->getAllConnectors();
	if(connectorMap.empty())
		throw EmptyCollectionException(ComponentType::TypeConnectorName);
	
	this->textUI->displayConnections(connectorMap);
}

void Presentation::displayEntities(){
	HashMap<string,Entity*> entityMap = erModel->getAllEntities();
	if(entityMap.empty())
		throw EmptyCollectionException(ComponentType::TypeEntityName);
	this->textUI->displayEntities(ComponentUtil::toComponentHashMap<Entity>(entityMap));
}

void Presentation::displayEntityAttributes(Entity* entity){
	HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
	if(attributeMap.empty())
		throw EmptyCollectionException(ComponentType::TypeAttributeName);
	this->textUI->displayEntityAttributes(entity,ComponentUtil::toComponentHashMap<Attribute>(attributeMap));
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
		this->textUI->alertException("wrong command,please input correct command.");
	}
	catch(Exception& exception){
		this->textUI->alertException(exception.getMessage());
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

void Presentation::setTextUI(TextUI* textUI){
	this->textUI = textUI;
}

CommandManager* Presentation::getCommandManager(){
	return this->commandManager;
}