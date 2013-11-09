#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"
#include <iostream>

GUIScene::GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI) : graphicalUI(graphicalUI),QGraphicsScene(left,top,width,height,graphicalUI){
}

GUIScene::~GUIScene(){
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QGraphicsScene::mousePressEvent(mouseEvent);
    this->graphicalUI->mousePress(mouseEvent->pos());
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QGraphicsScene::mouseMoveEvent(mouseEvent);
	this->graphicalUI->mouseMove(mouseEvent->pos());
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    this->graphicalUI->mouseRelease(mouseEvent->pos());
}