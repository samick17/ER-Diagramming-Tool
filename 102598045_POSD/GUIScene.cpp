#include "GUIScene.h"
#include "GraphicalUI.h"
#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include "GraphicalPresentation.h"

GUIScene::GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI) : graphicalUI(graphicalUI),QGraphicsScene(left,top,width,height,graphicalUI){
}

GUIScene::~GUIScene(){
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mousePress(position);
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mouseMove(position);
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF position = mouseEvent->scenePos();
    this->graphicalUI->mouseRelease(position);
}