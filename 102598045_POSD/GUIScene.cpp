#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"
#include "WidgetFactory.h"

GUIScene::GUIScene(QRectF sceneRect,GraphicalUI* graphicalUI,QGraphicsView* view) : QGraphicsScene(sceneRect,graphicalUI),graphicalUI(graphicalUI),view(view){
    this->graphicalPresentation = this->graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserver(this);
    this->connect(this,SIGNAL(onNotifyEvent()),this,SLOT(executeNotify()));
}

GUIScene::~GUIScene(){
    this->graphicalPresentation->unregisterObserver(this);
}

void GUIScene::notify(ISubject* subject){
    this->onNotifyEvent();
}

void GUIScene::displayDiagram(){
    this->clearAll();
    //display all
    set<ComponentData*> componentDataSet = this->graphicalPresentation->getAllComponentDataSet();
    WidgetFactory widgetFactory;
    for each(ComponentData* componentData in componentDataSet){
        BaseWidget* componentWidget = widgetFactory.createComponentWidget(componentData,this->graphicalPresentation);
        this->addWidget(componentWidget);
    }
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,ComponentData*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mousePressEvent(pointComponentPair.first,pointComponentPair.second);
    this->updateAll();
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,ComponentData*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mouseMoveEvent(pointComponentPair.first,pointComponentPair.second);
    this->updateAll();
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,ComponentData*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mouseReleaseEvent(pointComponentPair.first,pointComponentPair.second);
    this->updateAll();
}
//get component from widget
pair<Point,ComponentData*> GUIScene::getPointComponentPair(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    Point position = Point(qPosition.x(),qPosition.y());
    ComponentData* componentData = this->getComponentDataAtPosition(qPosition);
    return pair<Point,ComponentData*>(position,componentData);
}

void GUIScene::executeNotify(){
    this->graphicalPresentation->updateAllComponentData();
    this->displayDiagram();
}

ComponentData* GUIScene::getComponentDataAtPosition(QPointF qPosition){
    //if this graphicaItem cannot cast to 'ComponentWidget' ,the value of widget is NULL
    ComponentWidget* widget = dynamic_cast<ComponentWidget*>(this->itemAt(qPosition));
    ComponentData* componentData = NULL;
    if(widget)
        componentData = widget->getComponentData();
    return componentData;
}

void GUIScene::addWidget(BaseWidget* widget){
    this->addItem(widget);
    this->widgetList.push_back(widget);
    widget->updateWidget();
}

void GUIScene::updateAll(){
    for each(BaseWidget* widget in this->widgetList)
        widget->updateWidget();
    this->update();
}

void GUIScene::clearAll(){
    this->clear();
    //qt's scene will auto delete widget item,so the work we have to do just clear it.
    this->widgetList.clear();
}