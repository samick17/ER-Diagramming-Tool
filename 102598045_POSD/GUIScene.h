#pragma once

#include <QGraphicsScene>
#include "IObserver.h"

class GraphicalUI;
class BaseWidget;
class GraphicalPresentation;
class Component;

class GUIScene : public QGraphicsScene,public IObserver{
    Q_OBJECT
signals:
    void notifyEvent();
public:
    GUIScene(QRectF sceneRect,GraphicalUI* graphicalUI,QGraphicsView* view);
    ~GUIScene();

    void notify(ISubject* subject);
    void displayDiagram();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
private:
    GraphicalUI* graphicalUI;
    QGraphicsView* view;
    GraphicalPresentation* graphicalPresentation;
    QList<BaseWidget*> widgetList;
    Component* hasItemAtPosition(QPointF qPosition);
    void addWidget(BaseWidget* widget);
    void updateAll();
    void clearAll();
private slots:
    void executeNotify();
};