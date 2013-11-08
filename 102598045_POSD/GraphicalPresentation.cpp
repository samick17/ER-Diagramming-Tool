#include "GraphicalPresentation.h"
#include "ActionData.h"
#include "ApplicationSetting.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "WidgetDefaultSetting.h"
#include <algorithm>
#include "Number.h"
#include "ControllerEvent.h"
#include "ERModelUtil.h"
#include "StateFactory.h"
#include "StateID.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
    this->isCtrlPressed = false;
    this->state = NULL;
}

GraphicalPresentation::~GraphicalPresentation(){
    this->clearAllComponentWidget();
    delete this->state;
}

HashMap<string,ComponentWidget*> GraphicalPresentation::getAllComponentWidgets(){
    this->updateComponentWidgetMap();
    return this->componentWidgetMap;
}

State* GraphicalPresentation::getState(){
    return this->state;
}

void GraphicalPresentation::openFile(string filePath){
    this->presentation->openFile(filePath);
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
bool GraphicalPresentation::isSelected(ComponentWidget* selectedWidget){
    if(this->selectedWidgetList.contains(selectedWidget))
        return true;
    return false;
}

void GraphicalPresentation::selectWidget(ComponentWidget* selectedWidget){
    if(this->selectedWidgetList.contains(selectedWidget)){
        this->selectedWidgetList.removeOne(selectedWidget);
        selectedWidget->update();
        return;
    }
    QList<ComponentWidget*> widgetList = this->selectedWidgetList;
    if(!this->isCtrlPressed)
        this->selectedWidgetList.clear();
    this->selectedWidgetList.push_back(selectedWidget);
    selectedWidget->update();
    for each(ComponentWidget* widget in widgetList)
        widget->update();
}

void GraphicalPresentation::switchState(int stateID){
    if(this->state != NULL)
        delete this->state;
    StateFactory stateFactory;
    this->state = stateFactory.createState(stateID,this);
}
//key pressed
void GraphicalPresentation::keyCtrlPressed(){
    this->isCtrlPressed = true;
}

void GraphicalPresentation::keyCtrlReleased(){
    this->isCtrlPressed = false;
}

void GraphicalPresentation::registerSynchronizer(ISynchronizer* synchronizer){
    this->presentation->registerSynchronizer(synchronizer);
}

void GraphicalPresentation::unregisterSynchronizer(ISynchronizer* synchronizer){
    this->presentation->unregisterSynchronizer(synchronizer);
}

void GraphicalPresentation::sync(int syncEventType){
    this->presentation->sync(syncEventType);
}

void GraphicalPresentation::sync(ISynchronizer* synchronizer,int syncEventType){
    this->presentation->sync(synchronizer,syncEventType);
}

void GraphicalPresentation::clearAllComponentWidget(){
    this->componentWidgetMap.clear();
    this->selectedWidgetList.clear();
}
//update all from model to widget
void GraphicalPresentation::updateComponentWidgetMap(){
    this->clearAllComponentWidget();
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    //create relationShip
    int currentTotalHeight = 0;
    this->createRelationShipWidget(componentMap,this->presentation->getAllRelationShips(),currentTotalHeight);
    this->createRemainsEntityWidget(componentMap,currentTotalHeight);
    this->createRemainsAttributeWidget(componentMap,currentTotalHeight);
    this->createConnectorWidget(this->presentation->getAllConnectors());
}
//create relationship widgets and its connected entities
int GraphicalPresentation::createRelationShipWidget(HashMap<string,Component*>& componentMap,HashMap<string,RelationShip*> relationShipMap,int& currentHeight){
    WidgetFactory widgetFactory;
    for each(RelationShip* relationShip in this->presentation->getAllRelationShips()){
        HashMap<string,Entity*> connectedEntitiesMap = relationShip->getConnectedEntities();
        int totalHeight = this->createEntityWidget(componentMap,connectedEntitiesMap,currentHeight);
        int currentRelationShipHeight = currentHeight;
        if(!connectedEntitiesMap.empty())
            currentRelationShipHeight = totalHeight/connectedEntitiesMap.size();
        ComponentWidgetData componentWidgetData = ComponentWidgetData(relationShip->getName(),WidgetDefaultSetting::RelationShipHorizontalDistance,currentRelationShipHeight);
        ComponentWidget* relationShipWidget = widgetFactory.createComponentWidget(relationShip->getType(),componentWidgetData,this);
        this->componentWidgetMap.put(relationShip->getID(),relationShipWidget);
        componentMap.remove(relationShip->getID());
        currentHeight += WidgetDefaultSetting::RelationShipVerticalDistance;
    }
    return currentHeight;
}
//create entity widgets and its connected attributes
int GraphicalPresentation::createEntityWidget(HashMap<string,Component*>& componentMap,HashMap<string,Entity*> entityMap,int& currentHeight){
    WidgetFactory widgetFactory;
    int finalRelationShipHeight = 0;
    //int currentHeight = 0;
    for each(Entity* entity in entityMap){
        if(!componentMap.containsKey(entity->getID()))
            continue;
        this->createAttributeWidget(componentMap,entity->getConnectedAttributes(),currentHeight);
        int currentTotalHeight = WidgetDefaultSetting::AttributeVerticalDistance*entity->getConnectedAttributes().size();
        int entityHeight = currentHeight-((currentTotalHeight+WidgetDefaultSetting::Height)/Number::Two);
        ComponentWidgetData componentWidgetData = ComponentWidgetData(entity->getName(),WidgetDefaultSetting::EntityHorizontalDistance,entityHeight);
        ComponentWidget* entityWidget = widgetFactory.createComponentWidget(entity->getType(),componentWidgetData,this);
        this->componentWidgetMap.put(entity->getID(),entityWidget);
        componentMap.remove(entity->getID());
        finalRelationShipHeight += entityHeight;
        currentHeight += WidgetDefaultSetting::EntityVerticalDistance;
    }
    return currentHeight;
}
//create attribute widgets
int GraphicalPresentation::createAttributeWidget(HashMap<string,Component*>& componentMap,HashMap<string,Attribute*> attributeMap,int& attributeHeight){
    WidgetFactory widgetFactory;
    for each(Attribute* attribute in attributeMap){
        ComponentWidgetData componentWidgetData = ComponentWidgetData(attribute->getName(),WidgetDefaultSetting::AttributeHorizontalDistance,attributeHeight,attribute->isPrimaryKey());
        AttributeWidget* attributeWidget = static_cast<AttributeWidget*>(widgetFactory.createComponentWidget(attribute->getType(),componentWidgetData,this));
        this->componentWidgetMap.put(attribute->getID(),attributeWidget);
        componentMap.remove(attribute->getID());
        attributeHeight += WidgetDefaultSetting::AttributeVerticalDistance;
    }
    return attributeHeight;
}
//create connector widgets,and set property , e.g.text,line to draw
void GraphicalPresentation::createConnectorWidget(HashMap<string,Connector*> connectorMap){
    WidgetFactory widgetFactory;
    for each(Connector* connector in connectorMap){
        ComponentWidgetData componentWidgetData = ComponentWidgetData(connector->getName(),0,0);
        ConnectorWidget* connectorWidget = static_cast<ConnectorWidget*>(widgetFactory.createComponentWidget(connector->getType(),componentWidgetData,this));
        ComponentWidget* sourceWidget = this->componentWidgetMap.get(connector->getFirstConnectedNode()->getID());
        ComponentWidget* targetWidget = this->componentWidgetMap.get(connector->getSecondConnectedNode()->getID());
        this->setConnectorWidgetProperty(connectorWidget,sourceWidget,targetWidget);
        this->componentWidgetMap.put(connector->getID(),connectorWidget);
    }
}
//set connector widget's property
void GraphicalPresentation::setConnectorWidgetProperty(ConnectorWidget* connectorWidget,ComponentWidget* sourceWidget,ComponentWidget* targetWidget){
    QRectF sourceRect = sourceWidget->boundingRect();
    QRectF targetRect = targetWidget->boundingRect();
    QPointF sourceCenterLeft = QPointF(sourceRect.left(),sourceRect.center().y());
    QPointF sourceCenterRight = QPointF(sourceRect.right(),sourceRect.center().y());
    QPointF targetCenterLeft = QPointF(targetRect.left(),targetRect.center().y());
    QPointF targetCenterRight = QPointF(targetRect.right(),targetRect.center().y());
    QPointF deltaLeft = sourceCenterLeft-targetCenterRight;
    QPointF deltaRight = sourceCenterRight-targetCenterLeft;
    if(deltaLeft.manhattanLength() < deltaRight.manhattanLength())
        connectorWidget->setConnectionPoint(sourceCenterLeft,targetCenterRight);
    else 
        connectorWidget->setConnectionPoint(sourceCenterRight,targetCenterLeft);
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