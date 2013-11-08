#include "GUIScene.h"
#include "GraphicalUI.h"

GUIScene::GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI) : graphicalUI(graphicalUI),QGraphicsScene(left,top,width,height,graphicalUI){
}

GUIScene::~GUIScene(){
}

void GUIScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->graphicalUI->mousePress();
}

void GUIScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->graphicalUI->mouseMove();
}

void GUIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->graphicalUI->mouseRelease();
}