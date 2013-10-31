#pragma once

#include "ComponentWidget.h"

class AttributeWidget : public ComponentWidget{
public:
    AttributeWidget(QRectF rect,QGraphicsItem* parent = 0);
    ~AttributeWidget();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};