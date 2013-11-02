#include "GraphicalPresentation.h"
#include <QFileDialog>
#include "ActionData.h"
#include "ApplicationSetting.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "WidgetDefaultSetting.h"
#include <algorithm>
#include "Number.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
    this->isCtrlPressed = false;
}

GraphicalPresentation::~GraphicalPresentation(){
    this->clearAllComponentWidget();
}

HashMap<string,ComponentWidget*> GraphicalPresentation::getAllComponentWidgets(){
    this->updateComponentWidgetMap();
    return this->componentWidgetMap;
}

void GraphicalPresentation::openFile(){
    QFileDialog* openFileDialog = new QFileDialog(NULL, QString(ActionData::OpenFile.c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
    if(openFileDialog->exec()){
        QString filePath = openFileDialog->selectedFiles().first();	
        this->presentation->openFile(filePath.toStdString());
    }
    delete openFileDialog;
}

void GraphicalPresentation::saveFile(){
    QFileDialog* saveFileDialog = new QFileDialog(NULL, QString(ActionData::OpenFile.c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
    saveFileDialog->exec();
    QString filePath = saveFileDialog->selectedFiles().first();
    if(!filePath.isEmpty())
        this->presentation->saveFile(filePath.toStdString());
    delete saveFileDialog;
}

void GraphicalPresentation::close(){
    this->presentation->close();
}

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

void GraphicalPresentation::keyCtrlPressed(){
    this->isCtrlPressed = true;
}

void GraphicalPresentation::keyCtrlReleased(){
    this->isCtrlPressed = false;
}

void GraphicalPresentation::clearAllComponentWidget(){
    this->componentWidgetMap.clear();
    this->selectedWidgetList.clear();
}

void GraphicalPresentation::updateComponentWidgetMap(){
    this->clearAllComponentWidget();
    HashMap<string,Component*> componentMap;
    this->createRelationShipWidget(componentMap,this->presentation->getAllRelationShips());
    this->createRemainsEntityWidget(componentMap);
    this->createRemainsAttributeWidget(componentMap);
	this->createConnectorWidget(this->presentation->getAllConnectors());
}

void GraphicalPresentation::createRelationShipWidget(HashMap<string,Component*>& componentMap,HashMap<string,RelationShip*> relationShipMap){
    WidgetFactory widgetFactory;
    int relationShipHeight = 0;
    for each(RelationShip* relationShip in this->presentation->getAllRelationShips()){
        this->createEntityWidget(componentMap,relationShip->getConnectedEntities(),relationShipHeight);
        ComponentWidget* relationShipWidget = widgetFactory.createComponentWidget(relationShip->getType(),this);
        this->componentWidgetMap.put(relationShip->getID(),relationShipWidget);
        relationShipWidget->setText(relationShip->getName());
        componentMap.put(relationShip->getID(),relationShip);
        relationShipWidget->setPos(WidgetDefaultSetting::RelationShipHorizontalDistance,relationShipHeight);
    }
}

void GraphicalPresentation::createEntityWidget(HashMap<string,Component*>& componentMap,HashMap<string,Entity*> entityMap,int& relationShipHeight){
    WidgetFactory widgetFactory;
    int finalRelationShipHeight = 0;
    int attributeHeight = 0;
    for each(Entity* entity in entityMap){
        if(componentMap.containsKey(entity->getID()))
            continue;
        this->createAttributeWidget(componentMap,entity->getConnectedAttributes(),attributeHeight);
        int currentTotalHeight = WidgetDefaultSetting::AttributeVerticalDistance*entity->getConnectedAttributes().size();
        int entityHeight = attributeHeight - ((currentTotalHeight+WidgetDefaultSetting::Height)/Number::Two);
        ComponentWidget* entityWidget = widgetFactory.createComponentWidget(entity->getType(),this);
        this->componentWidgetMap.put(entity->getID(),entityWidget);
        entityWidget->setText(entity->getName());
        componentMap.put(entity->getID(),entity);
        entityWidget->setPos(WidgetDefaultSetting::EntityHorizontalDistance,entityHeight);
        finalRelationShipHeight += entityHeight;
    }
    //caculate relationship height
    if(!entityMap.empty())
        relationShipHeight = finalRelationShipHeight/entityMap.size();
}

void GraphicalPresentation::createAttributeWidget(HashMap<string,Component*>& componentMap,HashMap<string,Attribute*> attributeMap,int& attributeHeight){
    WidgetFactory widgetFactory;
    //HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
    for each(Attribute* attribute in attributeMap){
        ComponentWidget* attributeWidget = widgetFactory.createComponentWidget(attribute->getType(),this);
        this->componentWidgetMap.put(attribute->getID(),attributeWidget);
        attributeWidget->setText(attribute->getName());
        componentMap.put(attribute->getID(),attribute);
        attributeWidget->setPos(WidgetDefaultSetting::AttributeHorizontalDistance,attributeHeight);
        attributeHeight += WidgetDefaultSetting::AttributeVerticalDistance;
    }
}

void GraphicalPresentation::createConnectorWidget(HashMap<string,Connector*> connectorMap){
    WidgetFactory widgetFactory;
    for each(Connector* connector in connectorMap){
        ConnectorWidget* connectorWidget = static_cast<ConnectorWidget*>(widgetFactory.createComponentWidget(connector->getType(),this));
        ComponentWidget* sourceWidget = this->componentWidgetMap.get(connector->getFirstConnectedNode()->getID());
        ComponentWidget* targetWidget = this->componentWidgetMap.get(connector->getSecondConnectedNode()->getID());
        this->setConnectorWidget(connectorWidget,sourceWidget,targetWidget);
        connectorWidget->setText(connector->getName());
        this->componentWidgetMap.put(connector->getID(),connectorWidget);
    }
}

void GraphicalPresentation::setConnectorWidget(ConnectorWidget* connectorWidget,ComponentWidget* sourceWidget,ComponentWidget* targetWidget){
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

void GraphicalPresentation::createRemainsEntityWidget(HashMap<string,Component*>& componentMap){
    int currentHeight = 0;
    HashMap<string,Entity*> entityMap = this->presentation->getAllEntities();
    for each(Component* component in componentMap)
        if(entityMap.containsKey(component->getID()))
            entityMap.remove(component->getID());
    this->createEntityWidget(componentMap,entityMap,currentHeight);
}

void GraphicalPresentation::createRemainsAttributeWidget(HashMap<string,Component*>& componentMap){
    int currentHeight = 0;
    HashMap<string,Attribute*> attributeMap = this->presentation->getAllAttributes();
    for each(Component* component in componentMap)
        if(attributeMap.containsKey(component->getID()))
            attributeMap.remove(component->getID());
    this->createAttributeWidget(componentMap,attributeMap,currentHeight);
}