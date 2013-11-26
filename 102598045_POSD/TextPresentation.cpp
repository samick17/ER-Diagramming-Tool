#include "TextPresentation.h"
#include <iostream>
#include "Node.h"
#include "Entity.h"
#include "Connector.h"
#include "ERModel.h"
#include "ComponentUtil.h"
#include "StringUtil.h"
#include "NullPointerException.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"
#include "InstructionMenu.h"
#include "InstructionData.h"
#include "TextUIPresenter.h"
#include "ApplicationSetting.h"
#include "ControllerEvent.h"

TextPresentation::TextPresentation(Presentation* presentation) : presentation(presentation){
    string title = "Title "+ApplicationSetting::Title;
    system(title.c_str());
    this->instructionMenu = new InstructionMenu();
    this->textUIPresenter = new TextUIPresenter(this);
    this->initialSyncMap();
    this->initialCardinalityInputMap();
}

TextPresentation::~TextPresentation(){
    delete this->instructionMenu;
    delete this->textUIPresenter;
}

string TextPresentation::getInput(){
    string input;
    while(input.empty()){
        cout<<">";
        getline(cin,input);
    }
    return input;
}

InstructionMenu* TextPresentation::getInstructionMenu(){
    return this->instructionMenu;
}

TextUIPresenter* TextPresentation::getTextUIPresenter(){
    return this->textUIPresenter;
}

void TextPresentation::displayMenu(){
    this->textUIPresenter->displayMenu();
}

void TextPresentation::processCommand(){
    string commandKey = this->getInput();
    TextInstruction* textInstruction = NULL;
    try{
        InstructionData* instructionData = this->instructionMenu->getInstructionDataByKey(commandKey);
        //get new Command Function From Command Data
        NewInstructionFunction newInstructionFunction = instructionData->getNewInstructionFunction();
        textInstruction = newInstructionFunction();
        textInstruction->execute(this,this->textUIPresenter);
    }
    catch(NullPointerException){
        cout<<"wrong command,please input correct command."<<endl;
    }
    catch(Exception& exception){
        cout<<exception.getMessage()<<endl;
        delete textInstruction;
    }
}

HashMap<string,Table*> TextPresentation::getAllTables(){
    HashMap<string,Table*> tableMap = this->presentation->getAllTables();
    if(tableMap.empty())
        throw EmptyCollectionException("Tables");
    return tableMap;
}

HashMap<string,Component*> TextPresentation::getAllComponents(){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    if(componentMap.empty())
        throw EmptyCollectionException(ComponentType::TypeComponent);
    return componentMap;
}

HashMap<string,Connector*> TextPresentation::getAllConnections(){
    HashMap<string,Connector*> connectorMap = this->presentation->getAllConnectors();
    if(connectorMap.empty())
        throw EmptyCollectionException(ComponentType::TypeConnectorName);
    return connectorMap;
}

HashMap<string,Component*> TextPresentation::getAllEntities(){
    HashMap<string,Entity*> entityMap = this->presentation->getAllEntities();
    if(entityMap.empty())
        throw EmptyCollectionException(ComponentType::TypeEntityName);
    return ComponentUtil::toComponentHashMap<Entity>(entityMap);
}

HashMap<string,Component*> TextPresentation::getEntityAttributes(Entity* entity){
    HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
    if(attributeMap.empty())
        throw EmptyCollectionException(ComponentType::TypeAttributeName);
    return ComponentUtil::toComponentHashMap<Attribute>(attributeMap);
}

string TextPresentation::getCardinality(string input){
    try{
        return this->cardinalityInputMap.get(input);
    }
    catch(Exception&){
        throw Exception("The cardinality you entered doesn't exist. Please entered a valid one again");
    }
}

Component* TextPresentation::findComponent(){
    Component* find = NULL;
    while(!find){
        try{
            string input = this->getInput();
            find = this->presentation->getComponentByID(input);
        }
        catch(Exception& exception){
            cout<<exception.getMessage()<<endl;
        }
    }
    return find;
}

Entity* TextPresentation::findEntity(){
    Component* find = this->findComponent();
    while(typeid(*find).name() != typeid(Entity).name()){
        cout<<"The node '"+find->getID()+"' is not an entity. Please enter a valid one again."<<endl;
        find = this->findComponent();
    }
    return static_cast<Entity*>(find);
}

void TextPresentation::openFile(string filePath){
    this->presentation->openFile(filePath);
}

void TextPresentation::saveFile(string filePath){
    this->presentation->saveFile(filePath);
}

void TextPresentation::close(){
    this->presentation->close();
}

Node* TextPresentation::addNode(string nodeType){
    Node* node = this->presentation->addNode(nodeType);
    return node;
}

void TextPresentation::deleteComponent(string componentID){
    this->presentation->deleteComponent(componentID);
}

int TextPresentation::connectTwoNodes(Component* firstNode,Component* secondNode){
    int result = this->presentation->addConnection(firstNode,secondNode);
    return result;
}

void TextPresentation::setCardinality(Component* firstNode,Component* secondNode,string cardinality){
    Connector* connection = this->presentation->getNodesConnector(firstNode,secondNode);
    this->presentation->setCardinality(connection,cardinality);
}

void TextPresentation::setPrimaryKey(string componentID){
    this->presentation->setPrimaryKey(componentID);
}

void TextPresentation::redo(){
    this->presentation->redo();
}

void TextPresentation::undo(){
    this->presentation->undo();
}
void TextPresentation::registerSynchronizer(ISynchronizer* synchronizer){
    this->presentation->registerSynchronizer(synchronizer);
}

void TextPresentation::unregisterSynchronizer(ISynchronizer* synchronizer){
    this->presentation->unregisterSynchronizer(synchronizer);
}

void TextPresentation::sync(string syncEventType){
    this->presentation->sync(syncEventType);
}

void TextPresentation::initialSyncMap(){
    this->syncMap.put(ControllerEvent::OpenFile,&TextUIPresenter::displayDiagram);
    this->syncMap.put(ControllerEvent::AddNode,&TextUIPresenter::displayComponents);
    this->syncMap.put(ControllerEvent::DeleteComponent,&TextUIPresenter::displayComponents);
    this->syncMap.put(ControllerEvent::ConnectTwoNodes,&TextUIPresenter::displayConnections);
    this->syncMap.put(ControllerEvent::DisplayDiagram,&TextUIPresenter::displayDiagram);
    this->syncMap.put(ControllerEvent::DisplayTable,&TextUIPresenter::displayTable);
    this->syncMap.put(ControllerEvent::Undo,&TextUIPresenter::displayDiagram);
    this->syncMap.put(ControllerEvent::Redo,&TextUIPresenter::displayDiagram);
}

void TextPresentation::initialCardinalityInputMap(){
    unsigned int index = 0;
    for each(string cardinality in this->presentation->getCardinalityVector()){
        this->cardinalityInputMap.put(StringUtil::intToString(index),cardinality);
        index++;
    }
}

void TextPresentation::executeSync(string syncEventType){
    if(!syncMap.containsKey(syncEventType))
        return;
    try{
        ViewSyncFunction syncFunction = syncMap.get(syncEventType);
        (this->textUIPresenter->*syncFunction)();
    }
    catch(Exception& exception){
        cout<<exception.getMessage()<<endl;
    }
}