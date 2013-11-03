#include "Presentation.h"
#include "ERModel.h"
#include "OutputFileParser.h"
#include "InputFileParser.h"

Presentation::Presentation(ERModel* erModel) : erModel(erModel){
}

Presentation::~Presentation(){
}

void Presentation::openFile(string filePath){
    InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(filePath,erModel);
    this->erModel->notify();
}

void Presentation::saveFile(string filePath){
    OutputFileParser outputFileParser = OutputFileParser(this->erModel->getAllComponents());
    outputFileParser.parseModelToFile(filePath);
}

void Presentation::close(){
    exit(0);
}

Node* Presentation::addNode(string componentType){
    Node* node = this->erModel->addNode(componentType);
    this->erModel->notify();
    return node;
}

void Presentation::deleteComponent(Component* component){
    this->erModel->deleteComponent(component);
    this->erModel->notify();
}

int Presentation::addConnection(Component* firstNode,Component* secondNode){
    int result = this->erModel->addConnection(firstNode,secondNode);
    this->erModel->notify();
    return result;
}

void Presentation::redo(){
    this->erModel->redo();
    this->erModel->notify();
}

void Presentation::undo(){
    this->erModel->undo();
    this->erModel->notify();
}

Component* Presentation::getComponentByID(string id){
    return this->erModel->getComponentByID(id);
}

Connector* Presentation::getNodesConnector(Component* firstNode,Component* secondNode){
    return this->erModel->getNodesConnector(firstNode,secondNode);
}

HashMap<string,Component*> Presentation::getAllComponents(){
    return this->erModel->getAllComponents();
}

HashMap<string,Attribute*> Presentation::getAllAttributes(){
	return this->erModel->getAllAttributes();
}

HashMap<string,Entity*> Presentation::getAllEntities(){
    return this->erModel->getAllEntities();
}

HashMap<string,RelationShip*> Presentation::getAllRelationShips(){
    return this->erModel->getAllRelationShips();
}

HashMap<string,Connector*> Presentation::getAllConnectors(){
    return this->erModel->getAllConnectors();
}
//get All Tables
HashMap<string,Table*> Presentation::getAllTables(){
    return this->erModel->getAllTables();
}

void Presentation::registerObserver(IObserver* observer){
    this->erModel->registerObserver(observer);
}

void Presentation::unregisterObserver(IObserver* observer){
    this->erModel->unregisterObserver(observer);
}

void Presentation::notify(){
    this->erModel->notify();
}

void Presentation::notify(IObserver* observer){
    this->erModel->notify(observer);
}