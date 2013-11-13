#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>
#include "Component.h"
#include "IObserver.h"

class QGraphicsSceneMouseEvent;
class GraphicalPresentation;

using namespace std;

class ComponentWidget : public QGraphicsItem,public IObserver{
public:
    ComponentWidget(Component** component,GraphicalPresentation* graphicalPresentation);
    ~ComponentWidget();

    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    QRectF boundingRect() const;

    void notify(ISubject* subject);
protected:
    Component** component;
    GraphicalPresentation* graphicalPresentation;
    string getText();
    bool getIsUnderLine();
    string getComponentID();
    virtual void doUpdateWidget() = 0;

    virtual void doPaint(QPainter* painter) = 0;
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
private:
    void drawSelectedFrame(QPainter* painter);
    QRectF rect;
    string text;
    bool isUnderLine;
    string componentID;
    void updateWidget();
};