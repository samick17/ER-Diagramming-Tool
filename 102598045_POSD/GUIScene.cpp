#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"
#include "WidgetFactory.h"

GUIScene::GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI) : graphicalUI(graphicalUI),QGraphicsScene(left,top,width,height,graphicalUI){
    this->graphicalPresentation = this->graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserver(this);
}

GUIScene::~GUIScene(){
    this->graphicalUI->getGraphicalPresentation()->unregisterObserver(this);
}

void GUIScene::notify(ISubject* subject){
    this->update();
	this->displayDiagram();
}

void GUIScene::displayDiagram(){
    this->clear();
    HashMap<string,ComponentWidgetData> componentWidgetDataMap = this->graphicalPresentation->getAllComponentWidgetDatas();
    WidgetFactory widgetFactory;
    for(auto iterator = componentWidgetDataMap.rbegin();iterator!=componentWidgetDataMap.rend();iterator++){
        ComponentWidget* componentWidget = widgetFactory.createComponentWidget(*iterator,this->graphicalPresentation);
        this->addItem(componentWidget);
    }
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->QGraphicsScene::mousePressEvent(mouseEvent);
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mousePress(position);
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->QGraphicsScene::mouseMoveEvent(mouseEvent);
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mouseMove(position);
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->QGraphicsScene::mouseReleaseEvent(mouseEvent);
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mouseRelease(position);
}