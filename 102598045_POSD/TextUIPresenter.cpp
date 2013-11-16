#include "TextUIPresenter.h"
#include <iostream>
#include <iomanip>
#include "InstructionMenu.h"
#include "InstructionData.h"
#include "Table.h"
#include "Connector.h"
#include "StringSymbol.h"
#include "StringUtil.h"

TextUIPresenter::TextUIPresenter(TextPresentation* textPresentation) : textPresentation(textPresentation){
}

TextUIPresenter::~TextUIPresenter(){
}

void TextUIPresenter::displayTitle(string title){
    cout<<"  +----------------------------+"<<endl;
    cout<<" ¢x    "<<title<<setw(TITLE_WIDTH-title.size())<<"¢x"<<endl;
    cout<<"  +----------------------------+"<<endl;
}

void TextUIPresenter::displayMenu(){
    this->displayTitle("Commands Menu");
    cout<<" +------------------------------------------------------+"<<endl;
    InstructionMenu* instructionMenu = this->textPresentation->getInstructionMenu();
    for each(InstructionData* instructionData in instructionMenu->getInstructionDataMap()){
        int length = COMMAND_KEY_WIDTH+instructionData->getInfo().size();
        length = MENU_WIDTH-length;
        cout<<"¢x"<<setw(COMMAND_KEY_WIDTH)<<left<<instructionData->getKey()+".";
        cout<<right<<instructionData->getInfo()<<setw(length)<<"¢x"<<endl;
    }
    cout<<" +------------------------------------------------------+"<<endl;
}

void TextUIPresenter::displayTable(){
	HashMap<string,Table*> tableMap = this->textPresentation->getAllTables();
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

void TextUIPresenter::displayComponents(){
	HashMap<string,Component*> componentMap = this->textPresentation->getAllComponents();
    this->displayTitle("Components");
    this->displayComponentMap(componentMap);
}

void TextUIPresenter::displayConnections(){
	HashMap<string,Connector*> connectorMap = this->textPresentation->getAllConnections();
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

void TextUIPresenter::displayEntities(){
    this->displayTitle("Entities");
    HashMap<string,Component*> entityMap = this->textPresentation->getAllEntities();
    this->displayComponentMap(entityMap);
}

void TextUIPresenter::displayEntityAttributes(Entity* entity){
    HashMap<string,Component*> attributesMap = this->textPresentation->getEntityAttributes(entity);
    cout<<"Attributes of the entity '"<<entity->getID()<<"'"<<endl;
    this->displayComponentMap(attributesMap);
}

void TextUIPresenter::displayDiagram(){
    cout<<"The ER diagram is displayed as follows:"<<endl;
    this->displayComponents();
    cout<<endl;
    this->displayConnections();
}

void TextUIPresenter::displayComponentMap(HashMap<string,Component*> componentMap){
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

void TextUIPresenter::displayStringWithComma(string strStart,vector<string> stringVector,string strEnd){
    if(stringVector.empty())
        return;
    cout<<strStart;
    string stringWithComma = StringUtil::appendWithComma(stringVector);
    cout<<stringWithComma;
    cout<<strEnd;
}