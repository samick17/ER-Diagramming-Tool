#include "GUIScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include "GraphicalPresentation.h"
#include "WidgetFactory.h"
#include "DialogSetting.h"

GUIScene::GUIScene(GraphicalUI* graphicalUI) : QGraphicsScene(graphicalUI),graphicalUI(graphicalUI){
    this->graphicalPresentation = this->graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserverToModel(this);
    this->connect(this,SIGNAL(onNotifyEvent()),this,SLOT(executeNotify()));
}

GUIScene::~GUIScene(){
    this->graphicalPresentation->unregisterObserverToModel(this);
}

void GUIScene::notify(Subject* subject){
    this->onNotifyEvent();
}

void GUIScene::refreshAllWidgets(){
    this->clear();
    //display all
    HashMap<string,ComponentData*> componentDataMap = this->graphicalPresentation->getAllComponentDataMap();
    for each(ComponentData* componentData in componentDataMap)
        this->addWidget(componentData);
    ComponentData* componentDataForPreview = this->graphicalPresentation->getComponentDataForPreview();
    if(componentDataForPreview)
        this->addWidget(componentDataForPreview);
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,ComponentData*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mousePressEvent(pointComponentPair.first,pointComponentPair.second);
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,ComponentData*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mouseMoveEvent(pointComponentPair.first,pointComponentPair.second);
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,ComponentData*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mouseReleaseEvent(pointComponentPair.first,pointComponentPair.second);
    if(this->graphicalPresentation->needToSetCardinality())
        this->processSetCardinality();
}
//get component from widget
pair<Point,ComponentData*> GUIScene::getPointComponentPair(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    Point position = Point(qPosition.x(),qPosition.y());
    ComponentData* componentData = this->getComponentDataAtPosition(qPosition);
    return pair<Point,ComponentData*>(position,componentData);
}

void GUIScene::executeNotify(){
    this->refreshAllWidgets();
}

ComponentData* GUIScene::getComponentDataAtPosition(QPointF qPosition){
    //if this graphicaItem cannot cast to 'ComponentWidget' ,the value of widget is NULL
    ComponentWidget* widget = dynamic_cast<ComponentWidget*>(this->itemAt(qPosition));
    ComponentData* componentData = NULL;
    if(widget)
        componentData = widget->getComponentData();
    return componentData;
}
//add Widget and update
void GUIScene::addWidget(ComponentData* componentData){
    WidgetFactory widgetFactory;
    ComponentWidget* componentWidget = widgetFactory.createComponentWidget(componentData,this->graphicalPresentation);
    this->addItem(componentWidget);
    componentWidget->updateWidget();
    this->update();
}

void GUIScene::processSetCardinality(){
    bool isSetCardinality = false;
    while(!isSetCardinality){
        QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::SetCardinalityText.c_str()),QLineEdit::Normal,StringSymbol::Empty.c_str());
        isSetCardinality = this->graphicalPresentation->setCardinality(text.toStdString());
    }
}