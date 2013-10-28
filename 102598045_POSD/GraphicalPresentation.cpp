#include "GraphicalPresentation.h"
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
#include "OutputFileParser.h"

GraphicalPresentation::GraphicalPresentation(ERModel* erModel) : erModel(erModel){
}

GraphicalPresentation::~GraphicalPresentation(){
}

ERModel* GraphicalPresentation::getERModel(){
    return this->erModel;
}

//if alive == false,program will close
void GraphicalPresentation::close(){
    this->alive = false;
    cout<<"GooBye!"<<endl;
    exit(0);
}

string GraphicalPresentation::getInput(){
    string input;    
    while(input.length() == 0){
        cout<<">";
        getline(cin,input);        
    }
    return input;
}

void GraphicalPresentation::openFile(string filePath){
    InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(filePath,erModel);
}

void GraphicalPresentation::saveFile(string filePath){
    OutputFileParser outputFileParser = OutputFileParser(this->erModel->getAllComponents());
    outputFileParser.parseModelToFile(filePath);
}

void GraphicalPresentation::displayDiagram(){
    //display current diagram
    this->textUI->displayDiagram();
}

void GraphicalPresentation::displayTable(){
    HashMap<string,Table*> tableMap = erModel->getAllTables();
    if(tableMap.empty())
        throw EmptyCollectionException("Tables");
    this->textUI->displayTable(tableMap);
}

void GraphicalPresentation::displayComponents(){    
    HashMap<string,Component*> componentMap = erModel->getAllComponents();
    if(componentMap.empty())
        throw EmptyCollectionException(ComponentType::TypeComponent);
    this->textUI->displayComponents(componentMap);
}

void GraphicalPresentation::displayConnections(){    
    HashMap<string,Connector*> connectorMap = erModel->getAllConnectors();
    if(connectorMap.empty())
        throw EmptyCollectionException(ComponentType::TypeConnectorName);    
    this->textUI->displayConnections(connectorMap);
}

void GraphicalPresentation::displayEntities(){
    HashMap<string,Entity*> entityMap = erModel->getAllEntities();
    if(entityMap.empty())
        throw EmptyCollectionException(ComponentType::TypeEntityName);
    this->textUI->displayEntities(ComponentUtil::toComponentHashMap<Entity>(entityMap));
}

void GraphicalPresentation::displayEntityAttributes(Entity* entity){
    HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
    if(attributeMap.empty())
        throw EmptyCollectionException(ComponentType::TypeAttributeName);
    this->textUI->displayEntityAttributes(entity,ComponentUtil::toComponentHashMap<Attribute>(attributeMap));
}

void GraphicalPresentation::processCommand(string commandKey){
    
}

void GraphicalPresentation::executeCommand(Command* command){
    
}

void GraphicalPresentation::logMessage(string message,bool nextLine){
    cout<<message;
    if(nextLine)
        cout<<endl;
}

void GraphicalPresentation::setCommandManager(CommandManager* commandManager){
    this->commandManager = commandManager;
}

void GraphicalPresentation::setTextUI(TextUI* textUI){
    this->textUI = textUI;
}

CommandManager* GraphicalPresentation::getCommandManager(){
    return this->commandManager;
}