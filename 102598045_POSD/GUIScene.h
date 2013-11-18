#pragma once

#include <QGraphicsScene>
#include <utility>
#include "IObserver.h"
#include "Point.h"

class GraphicalUI;
class BaseWidget;
class GraphicalPresentation;
class Component;

using namespace std;

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
    Component* getComponentAtPosition(QPointF qPosition);
    pair<Point,Component*> getPointComponentPair(QGraphicsSceneMouseEvent* mouseEvent);
    void addWidget(BaseWidget* widget);
    void updateAll();
    void clearAll();
private slots:
    void executeNotify();
};