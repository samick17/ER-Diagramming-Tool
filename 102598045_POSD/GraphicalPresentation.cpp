#include "GraphicalPresentation.h"
#include "Node.h"
#include "ControllerEvent.h"
#include "ERModelUtil.h"
#include "StateID.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
    this->isCtrlPressed = false;
    this->lastPressedComponent = NULL;
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

Node* GraphicalPresentation::getLastAddedNode(){
    return this->lastAddedNode;
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

void GraphicalPresentation::addNode(string nodeType,string nodeName,Point centerPosition){
    Node* node = this->presentation->addNode(nodeType);
    this->lastAddedNode = node;
    node->setName(nodeName);
    node->setCenterPosition(centerPosition);
    this->setComponentDataForPreview(NULL);
    this->presentation->sync(ControllerEvent::DisplayDiagram);
}

void GraphicalPresentation::addConnection(Component* sourceComponent,Component* targetComponent){
    this->setComponentDataForPreview(NULL);
    try{
        this->presentation->addConnection(sourceComponent,targetComponent);
        this->presentation->sync(ControllerEvent::ConnectTwoNodes);
    }
    catch(Exception&){
        this->notify();
    }
}

void GraphicalPresentation::openFile(string filePath){
    try{
        this->presentation->openFile(filePath);
        this->unSelectAll();
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
    }
    catch(Exception&){
    }
}

void GraphicalPresentation::setComponentText(string componentID,string text){
    this->presentation->setComponentText(componentID,text);
}

void GraphicalPresentation::deleteComponent(){
    for each(string selectedID in this->selectedWidgetVector){
        try{
            this->presentation->deleteComponent(selectedID);
        }
        catch(Exception&){
        }
    }
    this->unSelectAll();
    this->sync(ControllerEvent::DeleteComponent);
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

void GraphicalPresentation::selectLastPressedWidget(){
    if(!this->lastPressedComponent)
        return;
    string lastPressedComponentID = this->lastPressedComponent->getID();
    if(!this->isWidgetSelected(lastPressedComponentID))
        this->selectedWidgetVector.push_back(lastPressedComponentID);
}

void GraphicalPresentation::moveSelectedWidget(Point deltaPosition){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    for each(string componentID in this->selectedWidgetVector){
        if(!componentMap.containsKey(componentID))
            continue;
        Component* component = componentMap.get(componentID);
        Point position = component->getRect().getPosition();
        component->setPosition(position+deltaPosition);
    }
}

void GraphicalPresentation::unSelectAll(){
    this->selectedWidgetVector.clear();
}

void GraphicalPresentation::switchState(int stateID){
    this->setComponentDataForPreview(NULL);
    this->stateSubject.switchState(stateID,this);
}
//key pressed
void GraphicalPresentation::setKeyCtrlState(bool isCtrlPressed){
    this->isCtrlPressed = isCtrlPressed;
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

void GraphicalPresentation::doRegisterObserver(IObserver* observer){
    this->presentation->registerObserver(observer);
}

void GraphicalPresentation::doUnregisterObserver(IObserver* observer){
    this->presentation->unregisterObserver(observer);
}

void GraphicalPresentation::mousePressEvent(Point position,ComponentData* componentData){
    this->lastPressedComponent = this->getComponentByComponentData(componentData);
    this->stateSubject.getState()->mousePressEvent(position);
}

void GraphicalPresentation::mouseMoveEvent(Point position,ComponentData* componentData){
    this->lastMovedComponent = this->getComponentByComponentData(componentData);
    this->stateSubject.getState()->mouseMoveEvent(position);
}

void GraphicalPresentation::mouseReleaseEvent(Point position,ComponentData* componentData){
    this->lastReleasedComponent = this->getComponentByComponentData(componentData);
    this->stateSubject.getState()->mouseReleaseEvent(position);
}

Component* GraphicalPresentation::getComponentByComponentData(ComponentData* componentData){
    if(!componentData)
        return NULL;
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    string componentID = componentData->getID();
    if(componentMap.containsKey(componentID))
        return componentMap.get(componentID);
    return NULL;
}