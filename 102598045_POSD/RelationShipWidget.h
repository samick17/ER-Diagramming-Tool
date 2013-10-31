#pragma once

#include "ComponentWidget.h"

class RelationShipWidget : public ComponentWidget{
public:
    RelationShipWidget(QRectF rect,QGraphicsItem* parent = 0);
    ~RelationShipWidget();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};