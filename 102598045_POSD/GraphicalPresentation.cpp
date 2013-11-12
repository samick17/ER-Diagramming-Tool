#include "GraphicalPresentation.h"
#include "ActionData.h"
#include "ApplicationSetting.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "WidgetDefaultSetting.h"
#include "Number.h"
#include "ControllerEvent.h"
#include "ERModelUtil.h"
#include "StateFactory.h"
#include "StateID.h"
#include "StateSubject.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
    this->isCtrlPressed = false;
    this->stateSubject = new StateSubject();
    this->presentation->registerObserver(this);
}

GraphicalPresentation::~GraphicalPresentation(){
    this->clearAllComponentWidget();
    delete this->stateSubject;
    this->presentation->unregisterObserver(this);
}

HashMap<string,ComponentWidgetData*> GraphicalPresentation::getAllComponentWidgetDatas(){
    return this->componentDataMap;
}

State* GraphicalPresentation::getState(){
    return this->stateSubject->getState();
}

StateSubject* GraphicalPresentation::getStateSubject(){
    return this->stateSubject;
}

void GraphicalPresentation::addNode(string nodeType,string nodeName,QPointF position){
    Node* node = this->presentation->addNode(nodeType);
    node->setName(nodeName);
    Rect rect = Rect(Point(position.x()-Size::DefaultSize().getWidth()/Number::Two,position.y()-Size::DefaultSize().getHeight()/Number::Two),Size::DefaultSize());
    this->componentDataMap.put(node->getID(),new ComponentWidgetData(node,rect));
    this->presentation->sync(ControllerEvent::DisplayDiagram);
}

void GraphicalPresentation::openFile(string filePath){
    this->clearAllComponentWidget();
    this->presentation->openFile(filePath);
    this->updateComponentWidgetMap();
    this->presentation->sync(ControllerEvent::DisplayDiagram);
}

void GraphicalPresentation::saveFile(string filePath){
    this->presentation->saveFile(filePath);
}
//close & exit application
void GraphicalPresentation::close(){
    this->presentation->close();
}
//is widget being selected?
bool GraphicalPresentation::isSelected(string componentID){
    if(this->selectedWidgetSet.find(componentID) != this->selectedWidgetSet.end())
        return true;
    return false;
}

void GraphicalPresentation::selectWidget(string componentID){
    bool isSelected = this->isSelected(componentID);
    if(this->isCtrlPressed){
        if(this->isSelected(componentID)){
            this->selectedWidgetSet.erase(componentID);
        }else {
            this->selectedWidgetSet.insert(componentID);
        }
    }else {
        this->selectedWidgetSet.clear();
        if(isSelected){
            this->selectedWidgetSet.erase(componentID);
        }else {
            this->selectedWidgetSet.insert(componentID);
        }
    }
    this->Subject::notify();
}

void GraphicalPresentation::switchState(int stateID){
    this->stateSubject->switchState(stateID,this);
}
//key pressed
void GraphicalPresentation::keyCtrlPressed(){
    this->isCtrlPressed = true;
}

void GraphicalPresentation::keyCtrlReleased(){
    this->isCtrlPressed = false;
}
//synchronized view
void GraphicalPresentation::registerSynchronizer(ISynchronizer* synchronizer){
    this->presentation->registerSynchronizer(synchronizer);
}

void GraphicalPresentation::unregisterSynchronizer(ISynchronizer* synchronizer){
    this->presentation->unregisterSynchronizer(synchronizer);
}

void GraphicalPresentation::sync(int syncEventType){
    this->presentation->sync(syncEventType);
}

void GraphicalPresentation::doRegisterObserver(IObserver* observer){
    this->presentation->registerObserver(observer);
}

void GraphicalPresentation::doUngisterObserver(IObserver* observer){
    this->presentation->unregisterObserver(observer);
}

void GraphicalPresentation::notify(ISubject* subject){
    this->updateComponentWidgetMap();
}

void GraphicalPresentation::clearAllComponentWidget(){
    for each(ComponentWidgetData* componentWidgetData in this->componentDataMap)
        delete componentWidgetData;
    this->componentDataMap.clear();
    this->selectedWidgetSet.clear();
}
//update all from model to widget
void GraphicalPresentation::updateComponentWidgetMap(){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    this->removeExistsOrDeletedComponentData(componentMap);
    int currentTotalHeight = 0;
    this->createRelationShipWidget(componentMap,this->presentation->getAllRelationShips(),currentTotalHeight);
    this->createRemainsEntityWidget(componentMap,currentTotalHeight);
    this->createRemainsAttributeWidget(componentMap,currentTotalHeight);
    this->createConnectorWidget(componentMap,this->presentation->getAllConnectors());
    this->Subject::notify();
}

void GraphicalPresentation::removeExistsOrDeletedComponentData(HashMap<string,Component*>& componentMap){
    HashMap<string,ComponentWidgetData*> comparedWidgetDataMapBuffer;
    for each(ComponentWidgetData* componentWidgetData in this->componentDataMap){
        Component* component = componentWidgetData->getComponent();
        string key = component->getID();
        if(!componentMap.containsKey(key))
            comparedWidgetDataMapBuffer.put(key,componentWidgetData);
        if(componentMap.containsKey(key))
            componentMap.remove(key);
    }
    for each(ComponentWidgetData* componentWidgetData in comparedWidgetDataMapBuffer){
        Component* component = componentWidgetData->getComponent();
        string key = component->getID();
        this->componentDataMap.remove(key);
    }
}
//create relationship widgets and its connected entities
int GraphicalPresentation::createRelationShipWidget(HashMap<string,Component*>& componentMap,HashMap<string,RelationShip*> relationShipMap,int& currentHeight){
    for each(RelationShip* relationShip in relationShipMap){
        if(!componentMap.containsKey(relationShip->getID()))
            continue;
        HashMap<string,Entity*> connectedEntitiesMap = relationShip->getConnectedEntities();
        int totalHeight = this->createEntityWidget(componentMap,connectedEntitiesMap,currentHeight);
        int currentRelationShipHeight = currentHeight;
        if(!connectedEntitiesMap.empty())
            currentRelationShipHeight = totalHeight/connectedEntitiesMap.size();
        Rect rect = Rect(Point(WidgetDefaultSetting::RelationShipHorizontalDistance,currentRelationShipHeight),Size::DefaultSize());
        ComponentWidgetData* componentWidgetData = new ComponentWidgetData(relationShip,rect);
        this->componentDataMap.put(relationShip->getID(),componentWidgetData);
        componentMap.remove(relationShip->getID());
        currentHeight += WidgetDefaultSetting::RelationShipVerticalDistance;
    }
    return currentHeight;
}
//create entity widgets and its connected attributes
int GraphicalPresentation::createEntityWidget(HashMap<string,Component*>& componentMap,HashMap<string,Entity*> entityMap,int& currentHeight){
    int finalRelationShipHeight = 0;
    for each(Entity* entity in entityMap){
        if(!componentMap.containsKey(entity->getID()))
            continue;
        this->createAttributeWidget(componentMap,entity->getConnectedAttributes(),currentHeight);
        int currentTotalHeight = WidgetDefaultSetting::AttributeVerticalDistance*entity->getConnectedAttributes().size();
        int entityHeight = currentHeight-((currentTotalHeight+WidgetDefaultSetting::Height)/Number::Two);
        Rect rect = Rect(Point(WidgetDefaultSetting::EntityHorizontalDistance,entityHeight),Size::DefaultSize());
        ComponentWidgetData* componentWidgetData = new ComponentWidgetData(entity,rect);
        this->componentDataMap.put(entity->getID(),componentWidgetData);
        componentMap.remove(entity->getID());
        finalRelationShipHeight += entityHeight;
        currentHeight += WidgetDefaultSetting::EntityVerticalDistance;
    }
    return currentHeight;
}
//create attribute widgets
int GraphicalPresentation::createAttributeWidget(HashMap<string,Component*>& componentMap,HashMap<string,Attribute*> attributeMap,int& attributeHeight){
    for each(Attribute* attribute in attributeMap){
        if(!componentMap.containsKey(attribute->getID()))
            continue;
        Rect rect = Rect(Point(WidgetDefaultSetting::AttributeHorizontalDistance,attributeHeight),Size::DefaultSize());
        ComponentWidgetData* componentWidgetData = new ComponentWidgetData(attribute,rect,attribute->isPrimaryKey());
        this->componentDataMap.put(attribute->getID(),componentWidgetData);
        componentMap.remove(attribute->getID());
        attributeHeight += WidgetDefaultSetting::AttributeVerticalDistance;
    }
    return attributeHeight;
}
//create connector widgets,and set property , e.g.text,line to draw
void GraphicalPresentation::createConnectorWidget(HashMap<string,Component*>& componentMap,HashMap<string,Connector*> connectorMap){
    for each(Connector* connector in connectorMap){
        if(!componentMap.containsKey(connector->getID()))
            continue;
        Rect rect = Rect(Point::DefaultPoint(),Size::DefaultSize());
        ComponentWidgetData* componentWidgetData = new ComponentWidgetData(connector,rect);
        this->componentDataMap.put(connector->getID(),componentWidgetData);
    }
}
//create unconnected entity widgets
void GraphicalPresentation::createRemainsEntityWidget(HashMap<string,Component*>& componentMap,int& currentHeight){
    HashMap<string,Entity*> entityMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(componentMap);
    this->createEntityWidget(componentMap,entityMap,currentHeight);
}
//create unconnected attribute widgets
void GraphicalPresentation::createRemainsAttributeWidget(HashMap<string,Component*>& componentMap,int& currentHeight){
    HashMap<string,Attribute*> attributeMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Attribute>(componentMap);
    this->createAttributeWidget(componentMap,attributeMap,currentHeight);
}