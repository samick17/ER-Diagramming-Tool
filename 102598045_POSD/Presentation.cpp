#include "Presentation.h"
#include "ERModel.h"
#include "IObserver.h"

Presentation::Presentation(ERModel* erModel) : erModel(erModel){
}

Presentation::~Presentation(){
}

void Presentation::openFile(string filePath){
    this->erModel->openFile(filePath);
}

void Presentation::saveFile(string filePath){
    this->erModel->saveFile(filePath);
}

void Presentation::close(){
    exit(0);
}

Node* Presentation::addNode(string componentType){
    return this->erModel->addNode(componentType);
}

void Presentation::deleteComponent(Component* component){
    this->erModel->deleteComponent(component);
}

int Presentation::addConnection(Component* firstNode,Component* secondNode){
    return this->erModel->addConnection(firstNode,secondNode);
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

void Presentation::registerSynchronizer(ISynchronizer* synchronizer){
    this->erModel->registerSynchronizer(synchronizer);
}

void Presentation::unregisterSynchronizer(ISynchronizer* synchronizer){
    this->erModel->unregisterSynchronizer(synchronizer);
}

void Presentation::sync(string syncEventType){
    this->erModel->sync(syncEventType);
}

void Presentation::registerObserver(IObserver* observer){
    this->erModel->registerObserver(observer);
}

void Presentation::unregisterObserver(IObserver* observer){
    this->erModel->unregisterObserver(observer);
}