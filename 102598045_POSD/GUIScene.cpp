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
    HashMap<string,ComponentWidgetData*> componentWidgetDataMap = this->graphicalPresentation->getAllComponentWidgetDatas();
    WidgetFactory widgetFactory;
    for each(ComponentWidgetData* componentWidgetData in componentWidgetDataMap){
        ComponentWidget* componentWidget = widgetFactory.createComponentWidget(*componentWidgetData,this->graphicalPresentation);
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

void GUIScene::executeNotify(){
    //this->update();
    this->displayDiagram();
    cout<<"notify scene"<<endl;
}