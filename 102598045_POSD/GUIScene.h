#pragma once

#include <QGraphicsScene>

class GraphicalUI;
class ComponentWidget;

class GUIScene : public QGraphicsScene{
public:
    GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI);
    ~GUIScene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
private:
    GraphicalUI* graphicalUI;
};