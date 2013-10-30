#include "GraphicalPresentation.h"
#include <iostream>
#include <iomanip>
#include "Entity.h"
#include "Connector.h"
#include "ComponentUtil.h"
#include "ERModelUtil.h"
#include "StringUtil.h"
#include "InstructionMenu.h"
#include "CommandManager.h"
#include "NullPointerException.h"
#include "EmptyCollectionException.h"
#include "StringSymbol.h"
#include "ComponentType.h"
#include "GraphicalUI.h"
#include <QFileDialog>

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
}

GraphicalPresentation::~GraphicalPresentation(){
}

void GraphicalPresentation::openFile(){
	QString fileName = QFileDialog::getOpenFileName(NULL, "Open File","C:\\","Files (*.erd)");
	this->presentation->openFile(fileName.toStdString());
}

void GraphicalPresentation::saveFile(){
	QString fileName = QFileDialog::getOpenFileName(NULL, "Open File","C:\\","Files (*.erd)");
	this->presentation->saveFile(fileName.toStdString());
}
//if alive == false,program will close
void GraphicalPresentation::close(){
	this->presentation->close();
}
void GraphicalPresentation::displayDiagram(){
    //display current diagram
	//this->graphicalUI->displayDiagram();
}

void GraphicalPresentation::displayTable(){
	HashMap<string,Table*> tableMap = this->presentation->getAllTables();
    if(tableMap.empty())
        throw EmptyCollectionException("Tables");
    //this->textUI->displayTable(tableMap);
}

void GraphicalPresentation::displayComponents(){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    if(componentMap.empty())
        throw EmptyCollectionException(ComponentType::TypeComponent);
    //this->textUI->displayComponents(componentMap);
}

void GraphicalPresentation::displayConnections(){    
    HashMap<string,Connector*> connectorMap = this->presentation->getAllConnectors();
    if(connectorMap.empty())
        throw EmptyCollectionException(ComponentType::TypeConnectorName);    
    //this->textUI->displayConnections(connectorMap);
}

void GraphicalPresentation::displayEntities(){
    HashMap<string,Entity*> entityMap = this->presentation->getAllEntities();
    if(entityMap.empty())
        throw EmptyCollectionException(ComponentType::TypeEntityName);
    //this->textUI->displayEntities(ComponentUtil::toComponentHashMap<Entity>(entityMap));
}

void GraphicalPresentation::displayEntityAttributes(Entity* entity){
    HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
    if(attributeMap.empty())
        throw EmptyCollectionException(ComponentType::TypeAttributeName);
    //this->textUI->displayEntityAttributes(entity,ComponentUtil::toComponentHashMap<Attribute>(attributeMap));
}

void GraphicalPresentation::setGraphicalUI(GraphicalUI* graphicalUI){
	this->graphicalUI = graphicalUI;
}