#include "TextUI.h"
#include <iostream>
#include <iomanip>
#include "CommandMenu.h"
#include "ApplicationSetting.h"
#include "StringUtil.h"
#include "StringSymbol.h"

TextUI::TextUI(Presentation* presentation) : presentation(presentation){
	string title = "Title "+ApplicationSetting::Title;
	system(title.c_str());
}

TextUI::~TextUI(){	
}

void TextUI::displayMenu(){
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

void TextUI::displayTitle(string title){	
	cout<<"  +----------------------------+"<<endl;
	cout<<" ¢x    "<<title<<setw(TITLE_WIDTH-title.size())<<"¢x"<<endl;
	cout<<"  +----------------------------+"<<endl;
}

void TextUI::displayTable(HashMap<string,Table*> tableMap){
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

void TextUI::displayComponents(HashMap<string,Component*> componentMap){
	this->displayTitle("Components");
	this->displayComponentMap(componentMap);
}

void TextUI::displayConnections(HashMap<string,Connector*> connectorMap){
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

void TextUI::displayEntities(HashMap<string,Component*> entityMap){
	this->displayTitle("Entities");
	this->displayComponentMap(entityMap);
}

void TextUI::displayEntityAttributes(Entity* entity,HashMap<string,Component*> attributesMap){
	cout<<"Attributes of the entity '"<<entity->getID()<<"'"<<endl;
	this->displayComponentMap(attributesMap);
}

void TextUI::displayDiagram(){
	cout<<"The ER diagram is displayed as follows:"<<endl;
	this->presentation->displayComponents();	
	cout<<endl;
	this->presentation->displayConnections();
}

void TextUI::displayComponentMap(HashMap<string,Component*> componentMap){	
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

void TextUI::displayStringWithComma(string strStart,vector<string> stringVector,string strEnd){
	if(stringVector.empty())
		return;
	cout<<strStart;
	string stringWithComma = StringUtil::appendWithComma(stringVector);
	cout<<stringWithComma;
	cout<<strEnd;	
}

void TextUI::processCommand(){	
	string input = this->presentation->getInput();
	this->presentation->processCommand(input);	
}

void TextUI::alertException(string information){
	cout<<information<<endl;
}