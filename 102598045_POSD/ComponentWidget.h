#pragma once

#include <QGraphicsItem>
#include <QColor>
#include "Component.h"

class QGraphicsSceneMouseEvent;

class ComponentWidget : public QGraphicsItem{
public:
    ComponentWidget(Component* component,QGraphicsItem* parent = 0);
    ~ComponentWidget();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) = 0;
    QRectF boundingRect() const;
protected:
    Component* component;

    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    void move(QPointF position);
};