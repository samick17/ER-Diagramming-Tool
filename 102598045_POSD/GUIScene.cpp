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
    HashMap<string,Component*>& componentMap = this->graphicalPresentation->getAllComponents();
    WidgetFactory widgetFactory;
    for each(Component* component in componentMap){
        BaseWidget* componentWidget = widgetFactory.createComponentWidget(component,this->graphicalPresentation);
        this->addWidget(componentWidget);
    }
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,Component*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mousePressEvent(pointComponentPair.first,pointComponentPair.second);
    this->updateAll();
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,Component*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mouseMoveEvent(pointComponentPair.first,pointComponentPair.second);
    this->updateAll();
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    pair<Point,Component*> pointComponentPair = this->getPointComponentPair(mouseEvent);
    this->graphicalPresentation->mouseReleaseEvent(pointComponentPair.first,pointComponentPair.second);
    this->updateAll();
}
//get component from widget
pair<Point,Component*> GUIScene::getPointComponentPair(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    Point position = Point(qPosition.x(),qPosition.y());
    Component* component = this->getComponentAtPosition(qPosition);
    return pair<Point,Component*>(position,component);
}

void GUIScene::executeNotify(){
    this->displayDiagram();
}

Component* GUIScene::getComponentAtPosition(QPointF qPosition){
    //if this graphicaItem cannot cast to 'ComponentWidget' ,the value of widget is NULL
    ComponentWidget* widget = dynamic_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    if(widget){
        component = widget->getComponent();
        //this->view->ensureVisible(widget);
    }
    return component;
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