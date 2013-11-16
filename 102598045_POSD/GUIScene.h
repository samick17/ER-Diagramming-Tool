#pragma once

#include <QGraphicsScene>
#include "IObserver.h"
#include "HashMap.h"

class GraphicalUI;
class BaseWidget;
class GraphicalPresentation;

class GUIScene : public QGraphicsScene,public IObserver{
    Q_OBJECT
signals:
    void notifyEvent();
public:
    GUIScene(qreal left,qreal top,qreal width,qreal height,GraphicalUI* graphicalUI);
    ~GUIScene();

    void notify(ISubject* subject);
    void displayDiagram();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
private:
    GraphicalUI* graphicalUI;
    GraphicalPresentation* graphicalPresentation;
    HashMap<string,BaseWidget*> componentWidgetMap;
    void updateAll();
    void clearAll();
private slots:
    void executeNotify();
};