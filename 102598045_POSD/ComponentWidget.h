#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>
#include "Component.h"

class QGraphicsSceneMouseEvent;
class GraphicalPresentation;

using namespace std;

class ComponentWidget : public QGraphicsItem{
public:
    ComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    ~ComponentWidget();

    void updateWidget();

    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    QRectF boundingRect() const;
protected:
    Component* component;
    GraphicalPresentation* graphicalPresentation;
    string getText();
    bool getIsUnderLine();
    string getComponentID();
    virtual void doUpdateWidget() = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void doPaint(QPainter* painter) = 0;
private:
    void drawSelectedFrame(QPainter* painter);
    QRectF rect;
    string text;
    bool isUnderLine;
    string componentID;
};