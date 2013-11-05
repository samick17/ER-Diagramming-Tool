#pragma once

#include "NodeWidget.h"

class RelationShipWidget : public NodeWidget{
public:
    RelationShipWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~RelationShipWidget();

    QPainterPath shape() const;
};