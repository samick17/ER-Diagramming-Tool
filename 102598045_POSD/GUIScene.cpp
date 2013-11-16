#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"
#include "WidgetFactory.h"
#include <iostream>

GUIScene::GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI) : graphicalUI(graphicalUI),QGraphicsScene(left,top,width,height,graphicalUI){
    this->graphicalPresentation = this->graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserver(this);
    this->connect(this,SIGNAL(notifyEvent()),this,SLOT(executeNotify()));
}

GUIScene::~GUIScene(){
    this->graphicalUI->getGraphicalPresentation()->unregisterObserver(this);
}

void GUIScene::notify(ISubject* subject){
    this->notifyEvent();
}

void GUIScene::displayDiagram(){
    this->clearAll();
    WidgetFactory widgetFactory;
    //display preview
    if(this->graphicalPresentation->getPreviewState()){
        widgetFactory.createPreviewWidget(this->graphicalPresentation);
    }
    //display all
    HashMap<string,Component*>& componentMap = this->graphicalPresentation->getAllComponents();
    
    for each(Component* component in componentMap){
        BaseWidget* componentWidget = widgetFactory.createComponentWidget(component,this->graphicalPresentation);
        this->addItem(componentWidget);
        this->componentWidgetMap.put(component->getID(),componentWidget);
        componentWidget->updateWidget();
    }
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    ComponentWidget* widget = static_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    Point position = Point(qPosition.x(),qPosition.y());
    if(widget){
        component = widget->getComponent();
    }
    this->graphicalPresentation->mousePressEvent(position,component);
    this->updateAll();
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    ComponentWidget* widget = static_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    Point position = Point(qPosition.x(),qPosition.y());
    if(widget){
        component = widget->getComponent();
    }
    this->graphicalPresentation->mouseMoveEvent(position,component);
    this->updateAll();
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    ComponentWidget* widget = static_cast<ComponentWidget*>(this->itemAt(qPosition));
    Component* component = NULL;
    Point position = Point(qPosition.x(),qPosition.y());
    if(widget){
        component = widget->getComponent();
    }
    this->graphicalPresentation->mouseReleaseEvent(position,component);
    this->updateAll();
}

void GUIScene::executeNotify(){
    this->displayDiagram();
}

void GUIScene::updateAll(){
    for each(ComponentWidget* widget in this->componentWidgetMap){
        widget->updateWidget();
    }
    this->update();
}

void GUIScene::clearAll(){
    this->clear();
    //qt's scene will auto delete widget item,so the work we have to do just clear it.
    this->componentWidgetMap.clear();
}