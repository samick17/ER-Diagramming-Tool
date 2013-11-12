#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>
#include "ComponentWidgetData.h"

class QGraphicsSceneMouseEvent;
class GraphicalPresentation;

using namespace std;

class ComponentWidget : public QGraphicsItem{
public:
    ComponentWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = NULL);
    ~ComponentWidget();

    Component* getComponent();
    void setText(string text);

    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    QRectF boundingRect() const;
protected:
    ComponentWidgetData componentWidgetData;
    QRectF rect;
    GraphicalPresentation* graphicalPresentation;

    string getText();
    bool getIsUnderLined();

    virtual void doPaint(QPainter* painter) = 0;
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
private:
    void drawSelectedFrame(QPainter* painter);
};