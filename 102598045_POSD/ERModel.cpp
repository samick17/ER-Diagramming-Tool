#include "ERModel.h"
#include "ERModelUtil.h"
#include "TableUtil.h"
#include "ComponentFactory.h"
#include "CommandFactory.h"
#include "ClipBoardStateFactory.h"
#include "NoSuchNodeException.h"
#include "InvalidConnectException.h"
#include "NoConnectionException.h"
#include "InvalidNodeTypeException.h"
#include "InputFileParser.h"
#include "HashMapUtil.h"
#include "InputFileProcess.h"
#include "OutputFileProcess.h"
#include "ClipBoardState.h"
#include "ClipBoardStateID.h"

ERModel::ERModel(){
    this->initialCountMap();
    this->resetCounting();
    //initialize clipBoard state
    this->clipBoardState = NULL;
    this->switchClipBoardState(ClipBoardStateID::NullClipBoardState);
}

ERModel::~ERModel(){
    this->resetERModel();
    if(this->clipBoardState)
        delete this->clipBoardState;
}

Node* ERModel::addNode(string nodeType){
    if(nodeType == ComponentType::TypeConnector)
        throw InvalidNodeTypeException();
    ComponentFactory componentFactory;
    Node* node = static_cast<Node*>(componentFactory.createComponent(nodeType));
    CommandFactory commandFactory;
    Command* addNodeCommand = commandFactory.createAddNodeCommand(this->componentMap,node);
    this->commandManager.execute(addNodeCommand);
    this->setNodePosition(nodeType,node);
    return node;
}

void ERModel::deleteComponent(vector<string> componentIDVector){
    CommandFactory commandFactory;
    Command* deleteComponentCommand = commandFactory.createDeleteMultiComponentCommand(this->componentMap,componentIDVector);
    this->commandManager.execute(deleteComponentCommand);
}
//return: NodeConnectionType
int ERModel::addConnection(Component* firstNode,Component* secondNode){
    if(!firstNode | !secondNode)
        throw InvalidConnectException(StringSymbol::Empty,StringSymbol::Empty);
    int result = firstNode->canConnectTo(secondNode);
    if(result == NodeConnectionType::ValidConnect || result == NodeConnectionType::ConnectEntityAndRelation){
        ComponentFactory componentFactory;
        Connector* connector = static_cast<Connector*>(componentFactory.createComponent(ComponentType::TypeConnector));
        CommandFactory commandFactory;
        Command* connectNodeCommand = commandFactory.createConnectNodeCommand(this->componentMap,firstNode,secondNode,connector);
        this->commandManager.execute(connectNodeCommand);
        connector->updateRect();
    }
    return result;
}

bool ERModel::canUndo(){
    return this->commandManager.canUndo();
}

bool ERModel::canRedo(){
    return this->commandManager.canRedo();
}

void ERModel::undo(){
    this->commandManager.undo();
}

void ERModel::redo(){
    this->commandManager.redo();
}

//set primarykey by its 'id',Exception Case : NoSuchNode,NoConnection
void ERModel::setPrimaryKey(string componentID){
    //make sure there has such component
    Attribute* attribute = dynamic_cast<Attribute*>(this->getComponentByID(componentID));
    //find entity & set its primary key
    HashMap<string,Entity*> entityMap = this->getAllEntities();
    Entity* connectedEntity = NULL;
    for each(Entity* entity in entityMap){
        if(entity->getConnectedAttributes().containsKey(componentID))
            connectedEntity = entity;
    }
    if(!connectedEntity)
        throw NoConnectionException(componentID);

    CommandFactory commandFactory;
    Command* setPrimaryKeyCommand = commandFactory.createSetPrimaryKeyCommand(attribute);
    this->commandManager.execute(setPrimaryKeyCommand);
}

//set cardinality without undo/redo
bool ERModel::setCardinality(Connector* connector,string cardinality){
    if(this->cardinality.hasCardinality(cardinality)){
        connector->setName(cardinality);
        return true;
    }
    return false;
}
//set component text & cardinality with undo/redo,Exception Case : NoSuchNode
void ERModel::setComponentText(string componentID,string text){
    Component* component = this->getComponentByID(componentID);

    Connector* connector = dynamic_cast<Connector*>(component);
    if(connector && (!this->cardinality.hasCardinality(text) || !connector->isCardinalityConnector()))
        return;

    CommandFactory commandFactory;
    Command* editTextOfComponentsCommand = commandFactory.createEditTextOfComponentsCommand(component,text);
    this->commandManager.execute(editTextOfComponentsCommand);
}

void ERModel::moveComponents(vector<string> selectedComponentsIDVector,Point mousePressPosition,Point mouseReleasePosition){
    if(mousePressPosition-mouseReleasePosition == Point::Zero)
        return;

    HashMap<string,Component*> selectedComponentMap = this->getComponentByIDVector(selectedComponentsIDVector);
    if(selectedComponentMap.empty())
        return;

    CommandFactory commandFactory;
    Command* moveComponentsCommand = commandFactory.createMoveComponentsCommand(selectedComponentMap,mousePressPosition,mouseReleasePosition);
    this->commandManager.execute(moveComponentsCommand);
}

void ERModel::openFile(string filePath){
    InputFileProcess inputFileProcess = InputFileProcess(filePath,this);
    inputFileProcess.openFile();
    /*InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(filePath,this);*/
    //open file should reset undo/redo state
    this->commandManager.popAllStack();
}

void ERModel::saveFile(string filePath){
    OutputFileProcess outputFileProcess = OutputFileProcess(filePath,this->componentMap);
    outputFileProcess.saveFile();
}

bool ERModel::canPaste(){
    return this->clipBoardState->canPaste();
}

void ERModel::cutComponents(vector<string> componentIDVector){
    this->switchClipBoardState(ClipBoardStateID::CutState);
    this->clipBoard.setData(this->getComponentByIDVector(componentIDVector));
    this->deleteComponent(componentIDVector);
}

void ERModel::copyComponents(vector<string> componentIDVector){
    this->switchClipBoardState(ClipBoardStateID::CopyState);
    this->clipBoard.setData(this->getComponentByIDVector(componentIDVector));
}

void ERModel::pasteComponents(){
    this->clipBoardState->paste();
}

void ERModel::switchClipBoardState(int clipBoardState){
    ClipBoardStateFactory clipBoardStateFactory;
    if(this->clipBoardState)
        delete this->clipBoardState;
    this->clipBoardState = clipBoardStateFactory.createState(clipBoardState,this);
}
//if doesn't contains such component, throw exception
Component* ERModel::getComponentByID(string id){
    if(this->componentMap.containsKey(id))
        return this->componentMap.get(id);
    throw NoSuchNodeException(id);
}
//return: firstNode & secondNode's connector
Connector* ERModel::getNodesConnector(Component* firstNode,Component* secondNode){
    Connector* connection = NULL;
    if(this->componentMap.containsKey(firstNode->getID()) && 
        this->componentMap.containsKey(secondNode->getID())){
        HashMap<string,Connector*> connections = this->getAllConnectors();
        for each(Connector* connector in connections){
            if(connector->isNodesConnection(firstNode,secondNode)){
                connection = connector;
                break;
            }
        }
    }
    return connection;
}

Cardinality* ERModel::getCardinality(){
    return &this->cardinality;
}

HashMap<string,Component*> ERModel::getAllComponents(){
    return this->componentMap;
}

HashMap<string,Attribute*> ERModel::getAllAttributes(){
    HashMap<string,Attribute*> attributeMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Attribute>(this->componentMap);
    return attributeMap;
}

HashMap<string,Connector*> ERModel::getAllConnectors(){
    HashMap<string,Connector*> connectorMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(this->componentMap);
    return connectorMap;
}

HashMap<string,Entity*> ERModel::getAllEntities(){
    HashMap<string,Entity*> entityMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(this->getAllComponents());
    return entityMap;
}

HashMap<string,RelationShip*> ERModel::getAllRelationShips(){
    HashMap<string,RelationShip*> relationShipMap = ERModelUtil::convertComponentHashMapToTypeHashMap<RelationShip>(this->getAllComponents());
    return relationShipMap;
}
//get All Tables
HashMap<string,Table*> ERModel::getAllTables(){
    return TableUtil::convertToTableMap(this->tableManager,this->getAllEntities(),this->getAllRelationShips());
}
//clear all components & delete it
void ERModel::resetERModel(){
    ComponentFactory componentFactory;
    componentFactory.resetFactory();
    this->commandManager.popAllStack();
    this->resetCounting();
    this->switchClipBoardState(ClipBoardStateID::NullClipBoardState);

    HashMapUtil::deleteAll(this->componentMap);
}

void ERModel::registerSynchronizer(ISynchronizer* synchronizer){
    synchronizerVector.push_back(synchronizer);
}

void ERModel::unregisterSynchronizer(ISynchronizer* synchronizer){
    auto synchronizerIterator = find(synchronizerVector.begin(),synchronizerVector.end(),synchronizer);
    synchronizerVector.erase(synchronizerIterator);
}

void ERModel::sync(string syncEventType){
    for each(ISynchronizer* synchronizer in this->synchronizerVector)
        synchronizer->sync(syncEventType);
}

void ERModel::initialCountMap(){
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeAttribute,WidgetDefaultSetting::AttributeOffsetX));
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeEntity,WidgetDefaultSetting::EntityOffsetX));
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeRelationShip,WidgetDefaultSetting::RelationShipOffsetX));
    this->componentTypeCountMap.put(ComponentType::TypeAttribute,&this->attributeCount);
    this->componentTypeCountMap.put(ComponentType::TypeEntity,&this->entityCount);
    this->componentTypeCountMap.put(ComponentType::TypeRelationShip,&this->relationShipCount);
}

void ERModel::resetCounting(){
    this->attributeCount = 0;
    this->entityCount = 0;
    this->relationShipCount = 0;
}

void ERModel::setNodePosition(string componentType,Node* node){
    auto countIterator = this->componentTypeCountMap.get(componentType);
    double positionX = componentTypeMapOffsetX.find(componentType)->second;
    double positionY = WidgetDefaultSetting::WidgetStartY+(*countIterator)*WidgetDefaultSetting::WidgetOffsetY;
    node->setPosition(Point(positionX,positionY));
    (*countIterator)++;
}

HashMap<string,Component*> ERModel::getComponentByIDVector(vector<string> componentIDVector){
    HashMap<string,Component*> resultMap;
    for each(string componentID in componentIDVector)
        if(this->componentMap.containsKey(componentID))
            resultMap.put(componentID,this->componentMap.get(componentID));
    return resultMap;
}