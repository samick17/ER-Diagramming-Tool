#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"
#include "WidgetFactory.h"

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
    HashMap<string,Component*>& componentMap = this->graphicalPresentation->getAllComponents();
    WidgetFactory widgetFactory;
    for each(Component* component in componentMap){
        ComponentWidget* componentWidget = widgetFactory.createComponentWidget(component,this->graphicalPresentation);
        this->addItem(componentWidget);
        componentWidget->updateWidget();
    }
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->QGraphicsScene::mousePressEvent(mouseEvent);
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mousePress(position);
    this->updateAll();
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->QGraphicsScene::mouseMoveEvent(mouseEvent);
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mouseMove(position);
    this->updateAll();
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->QGraphicsScene::mouseReleaseEvent(mouseEvent);
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mouseRelease(position);
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