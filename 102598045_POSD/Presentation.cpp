#include "Presentation.h"
#include "ERModel.h"
#include "ApplicationSetting.h"

Presentation::Presentation(ERModel* erModel) : erModel(erModel){
}

Presentation::~Presentation(){
}

const char* Presentation::getTitle(){
    return this->erModel->isNeedToSave()?ApplicationSetting::TitleAlertSave.c_str():ApplicationSetting::Title.c_str();
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

Node* Presentation::addNode(string nodeType){
    return this->erModel->addNode(nodeType);
}

void Presentation::deleteComponent(vector<string> componentIDVector){
    this->erModel->deleteComponent(componentIDVector);
}

int Presentation::addConnection(Component* firstNode,Component* secondNode){
    return this->erModel->addConnection(firstNode,secondNode);
}

bool Presentation::canRedo(){
    return this->erModel->canRedo();
}

bool Presentation::canUndo(){
    return this->erModel->canUndo();
}

bool Presentation::isNeedToSave(){
    return this->erModel->isNeedToSave();
}

void Presentation::redo(){
    this->erModel->redo();
}

void Presentation::undo(){
    this->erModel->undo();
}

bool Presentation::setCardinality(Connector* connector,string cardinality){
    return this->erModel->setCardinality(connector,cardinality);
}

void Presentation::setPrimaryKey(string componentID){
    this->erModel->setPrimaryKey(componentID);
}

void Presentation::setComponentText(string componentID,string text){
    this->erModel->setComponentText(componentID,text);
}

void Presentation::moveComponents(vector<string> selectedComponentsIDVector,Point mousePressPosition,Point mouseReleasePosition){
    this->erModel->moveComponents(selectedComponentsIDVector,mousePressPosition,mouseReleasePosition);
}

bool Presentation::canPaste(){
    return this->erModel->canPaste();
}

void Presentation::cutComponents(vector<string> componentIDVector){
    this->erModel->cutComponents(componentIDVector);
}

void Presentation::copyComponents(vector<string> componentIDVector){
    this->erModel->copyComponents(componentIDVector);
}

void Presentation::pasteComponents(){
    this->erModel->pasteComponents();
}

Component* Presentation::getComponentByID(string id){
    return this->erModel->getComponentByID(id);
}

Connector* Presentation::getNodesConnector(Component* firstNode,Component* secondNode){
    return this->erModel->getNodesConnector(firstNode,secondNode);
}

Cardinality* Presentation::getCardinality(){
    return this->erModel->getCardinality();
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

void Presentation::registerObserverToModel(IObserver* observer){
    this->erModel->registerObserver(observer);
}

void Presentation::unregisterObserverToModel(IObserver* observer){
    this->erModel->unregisterObserver(observer);
}

void Presentation::notifyModel(){
    this->erModel->notify();
}