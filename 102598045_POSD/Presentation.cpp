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
    return node;
}

void Presentation::deleteComponent(Component* component){
    this->erModel->deleteComponent(component);
}

int Presentation::addConnection(Component* firstNode,Component* secondNode){
    int result = this->erModel->addConnection(firstNode,secondNode);
    return result;
}

void Presentation::redo(){
    this->erModel->redo();
}

void Presentation::undo(){
    this->erModel->undo();
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

void Presentation::notify(int notifiedEventType){
    this->erModel->notify(notifiedEventType);
}

void Presentation::notify(IObserver* observer,int notifiedEventType){
    this->erModel->notify(observer,notifiedEventType);
}