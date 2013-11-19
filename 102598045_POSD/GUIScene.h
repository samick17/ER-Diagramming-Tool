#pragma once

#include <QGraphicsScene>
#include <utility>
#include "IObserver.h"
#include "Point.h"

class GraphicalUI;
class ComponentWidget;
class GraphicalPresentation;
class ComponentData;

using namespace std;

class GUIScene : public QGraphicsScene,public IObserver{
    Q_OBJECT
signals:
    void onNotifyEvent();
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
    QList<ComponentWidget*> widgetList;
    ComponentData* getComponentDataAtPosition(QPointF qPosition);
    pair<Point,ComponentData*> getPointComponentPair(QGraphicsSceneMouseEvent* mouseEvent);
    void addWidget(ComponentWidget* widget);
    void updateAll();
    void clearAll();
private slots:
    void executeNotify();
};