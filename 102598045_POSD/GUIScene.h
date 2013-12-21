#pragma once

#include <QGraphicsScene>
#include <QMutex>
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
    GUIScene(GraphicalUI* graphicalUI);
    ~GUIScene();

    void notify(Subject* subject);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
private:
    void refresh();
    ComponentData* getComponentDataAtPosition(QPointF qPosition);
    pair<Point,ComponentData*> getPointComponentPair(QGraphicsSceneMouseEvent* mouseEvent);
    void addWidget(ComponentData* componentData);
    void processSetCardinality();
    GraphicalUI* graphicalUI;
    GraphicalPresentation* graphicalPresentation;
    QMutex mutex;
private slots:
    void executeNotify();
};