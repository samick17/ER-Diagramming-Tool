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
    this->clear();
	//display preview

	//display all
    HashMap<string,Component*>& componentMap = this->graphicalPresentation->getAllComponents();
    WidgetFactory widgetFactory;
    for each(Component* component in componentMap){
        ComponentWidget* componentWidget = widgetFactory.createComponentWidget(component,this->graphicalPresentation);
        this->addItem(componentWidget);
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
    for each(QGraphicsItem* component in this->items()){
        ComponentWidget* widget = static_cast<ComponentWidget*>(component);
		widget->updateWidget();
    }
    this->update();
}