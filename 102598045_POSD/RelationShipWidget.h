#pragma once

#include "ComponentWidget.h"

class RelationShipWidget : public ComponentWidget{
public:
    RelationShipWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~RelationShipWidget();

    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};