#pragma once

#include "ComponentWidget.h"

class RelationShipWidget : public ComponentWidget{
public:
    RelationShipWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~RelationShipWidget();

    QPainterPath shape() const;
protected:
    void doPaint(QPainter* painter);
};