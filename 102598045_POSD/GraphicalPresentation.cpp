#include "GraphicalPresentation.h"
#include "Node.h"
#include "ControllerEvent.h"
#include "StateID.h"
#include "Connector.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
    this->isCtrlPressed = false;
    this->isDisplayDBTable = false;
    this->lastAddedConnector = NULL;
    this->lastPressedComponent = NULL;
    this->lastMovedComponent = NULL;
    this->lastReleasedComponent = NULL;
    this->componentDataForPreview = NULL;
}

GraphicalPresentation::~GraphicalPresentation(){
    this->deleteComponentDataForPreview();
}

StateSubject* GraphicalPresentation::getStateSubject(){
    return &this->stateSubject;
}

HashMap<string,ComponentData*> GraphicalPresentation::getAllComponentDataMap(){
    return this->componentDataMap;
}

HashMap<string,Table*> GraphicalPresentation::getAllTables(){
    return this->presentation->getAllTables();
}

ComponentData* GraphicalPresentation::getComponentDataForPreview(){
    return this->componentDataForPreview;
}

void GraphicalPresentation::setComponentDataForPreview(ComponentData* componentDataForPreview){
    this->deleteComponentDataForPreview();
    this->componentDataForPreview = componentDataForPreview;
}

void GraphicalPresentation::deleteComponentDataForPreview(){
    if(this->componentDataForPreview){
        delete this->componentDataForPreview;
        this->componentDataForPreview = NULL;
    }
}

void GraphicalPresentation::updateAllComponentData(){
    this->componentDataMap.clear();
    for each(Component* component in this->presentation->getAllComponents())
        this->componentDataMap.put(component->getID(),component->getComponentData());
}

Component* GraphicalPresentation::getLastPressedComponent(){
    return this->lastPressedComponent;
}

Component* GraphicalPresentation::getLastMovedComponent(){
    return this->lastMovedComponent;
}

Component* GraphicalPresentation::getLastReleasedComponent(){
    return this->lastReleasedComponent;
}

bool GraphicalPresentation::getIsDisplayDBTable(){
    return this->isDisplayDBTable;
}

void GraphicalPresentation::addNode(string nodeType,string nodeName,Point centerPosition){
    Node* node = this->presentation->addNode(nodeType);
    node->setName(nodeName);
    node->setCenterPosition(centerPosition);
    //preview should be invisible
    this->setComponentDataForPreview(NULL);
    this->presentation->sync(ControllerEvent::DisplayDiagram);
}

void GraphicalPresentation::addConnection(Component* sourceComponent,Component* targetComponent){
    this->setComponentDataForPreview(NULL);
    try{
        this->presentation->addConnection(sourceComponent,targetComponent);
        this->lastAddedConnector = this->presentation->getNodesConnector(sourceComponent,targetComponent);
        this->presentation->sync(ControllerEvent::ConnectTwoNodes);
    }
    catch(Exception&){
        this->notifyModel();
    }
}

void GraphicalPresentation::openFile(string filePath){
    try{
        this->presentation->openFile(filePath);
        this->isDisplayDBTable = false;
        this->unSelectAll();
        this->setComponentDataForPreview(NULL);
        this->presentation->sync(ControllerEvent::DisplayDiagram);
    }
    catch(Exception&){
    }
}

void GraphicalPresentation::saveFile(string filePath){
        this->presentation->saveFile(filePath);
}
//close & exit application
void GraphicalPresentation::close(){
    this->presentation->close();
}

void GraphicalPresentation::undo(){
    try{
        this->presentation->undo();
        this->sync(ControllerEvent::Undo);
    }
    catch(Exception&){
    }
}

void GraphicalPresentation::redo(){
    try{
        this->presentation->redo();
        this->sync(ControllerEvent::Redo);
    }
    catch(Exception&){
    }
}

void GraphicalPresentation::setPrimaryKey(string componentID){
    try{
        this->presentation->setPrimaryKey(componentID);
        this->sync(ControllerEvent::DisplayTable);
    }
    catch(Exception&){
    }
}

void GraphicalPresentation::setComponentText(string componentID,string text){
    this->presentation->setComponentText(componentID,text);
    this->sync(ControllerEvent::DisplayDiagram);
}

//delete all selected components
void GraphicalPresentation::deleteComponent(){
    this->presentation->deleteComponent(this->selectedWidgetVector);
    this->unSelectAll();
    this->sync(ControllerEvent::DeleteComponent);
}

bool GraphicalPresentation::isSelectAnyWidgets(){
    return !this->selectedWidgetVector.empty();
}

bool GraphicalPresentation::canPasteWidgets(){
    return false;
}

bool GraphicalPresentation::canUndo(){
    return this->presentation->canUndo();
}

bool GraphicalPresentation::canRedo(){
    return this->presentation->canRedo();
}

//is widget being selected?
bool GraphicalPresentation::isWidgetSelected(string componentID){
    auto iterator = find(this->selectedWidgetVector.begin(),this->selectedWidgetVector.end(),componentID);
    if(iterator != this->selectedWidgetVector.end())
        return true;
    return false;
}
//select widget : highlight/unhilight selected,notify all
void GraphicalPresentation::selectWidget(){
    if(!this->lastPressedComponent){
        if(!this->isCtrlPressed)
            this->unSelectAll();
        return;
    }
    string lastPressedComponentID = this->lastPressedComponent->getID();
    bool isSelected = this->isWidgetSelected(lastPressedComponentID);
    if(!this->isCtrlPressed)
        this->selectedWidgetVector.clear();
    if(!isSelected)
        this->selectedWidgetVector.push_back(lastPressedComponentID);
    else {
        auto iterator = find(this->selectedWidgetVector.begin(),this->selectedWidgetVector.end(),lastPressedComponentID);
        if(iterator != this->selectedWidgetVector.end())
            this->selectedWidgetVector.erase(iterator);
    }
}
//set last pressed widget be selected
void GraphicalPresentation::selectLastPressedWidget(){
    if(!this->lastPressedComponent)
        return;
    string lastPressedComponentID = this->lastPressedComponent->getID();
    if(!this->isWidgetSelected(lastPressedComponentID))
        this->selectedWidgetVector.push_back(lastPressedComponentID);
}

void GraphicalPresentation::previewMoveSelectedWidget(Point deltaPosition){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    for each(string componentID in this->selectedWidgetVector){
         if(!componentMap.containsKey(componentID))
             continue;
         Component* component = componentMap.get(componentID);
         Point position = component->getRect().getPosition();
         component->setPosition(position+deltaPosition);
    }
}
//move all selected widget
void GraphicalPresentation::moveSelectedWidget(Point mousePressPosition,Point mouseReleasePosition){
    this->presentation->moveSelectedComponent(this->selectedWidgetVector,mousePressPosition,mouseReleasePosition);
}

void GraphicalPresentation::unSelectAll(){
    this->selectedWidgetVector.clear();
}

void GraphicalPresentation::switchState(int stateID){
    this->stateSubject.switchState(stateID,this);
}

void GraphicalPresentation::switchDisplayDBTable(){
    this->isDisplayDBTable = !this->isDisplayDBTable;
}
//key pressed
void GraphicalPresentation::setKeyCtrlState(bool isCtrlPressed){
    this->isCtrlPressed = isCtrlPressed;
}

bool GraphicalPresentation::needToSetCardinality(){
    if(this->lastAddedConnector == NULL)
        return false;
    return this->lastAddedConnector->isCardinalityConnector();
}

bool GraphicalPresentation::setCardinality(string cardinality){
    if(!this->needToSetCardinality())
        return false;
    bool isSetCardinalitySucceed = this->presentation->setCardinality(this->lastAddedConnector,cardinality);
    if(isSetCardinalitySucceed){
        this->lastAddedConnector = NULL;
        this->notifyModel();
    }
    return isSetCardinalitySucceed;
}

//synchronized view
void GraphicalPresentation::registerSynchronizer(ISynchronizer* synchronizer){
    this->presentation->registerSynchronizer(synchronizer);
}

void GraphicalPresentation::unregisterSynchronizer(ISynchronizer* synchronizer){
    this->presentation->unregisterSynchronizer(synchronizer);
}

void GraphicalPresentation::sync(string syncEventType){
    this->presentation->sync(syncEventType);
}

void GraphicalPresentation::registerObserverToModel(IObserver* observer){
    this->presentation->registerObserverToModel(observer);
}

void GraphicalPresentation::unregisterObserverToModel(IObserver* observer){
    this->presentation->unregisterObserverToModel(observer);
}

void GraphicalPresentation::notifyModel(){
    this->presentation->notifyModel();
}

void GraphicalPresentation::mousePressEvent(Point position,ComponentData* componentData){
    this->lastPressedComponent = this->getComponentByComponentData(componentData);
    this->stateSubject.mousePressEvent(position);
}

void GraphicalPresentation::mouseMoveEvent(Point position,ComponentData* componentData){
    this->lastMovedComponent = this->getComponentByComponentData(componentData);
    this->stateSubject.mouseMoveEvent(position);
}

void GraphicalPresentation::mouseReleaseEvent(Point position,ComponentData* componentData){
    this->lastReleasedComponent = this->getComponentByComponentData(componentData);
    this->stateSubject.mouseReleaseEvent(position);
}

Component* GraphicalPresentation::getComponentByComponentData(ComponentData* componentData){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    for each(Component* component in componentMap)
        if(component->getComponentData() == componentData)
            return component;
    return NULL;
}