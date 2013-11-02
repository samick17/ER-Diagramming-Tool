#pragma once

#include "ComponentWidget.h"

class AttributeWidget : public ComponentWidget{
public:
    AttributeWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~AttributeWidget();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
private:
    QPolygon getDiamondPolygon(QRectF rect);
};