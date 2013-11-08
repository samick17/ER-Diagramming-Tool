#pragma once

#include "NodeWidget.h"

class RelationShipWidget : public NodeWidget{
public:
    RelationShipWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = NULL);
    ~RelationShipWidget();

    QPainterPath shape() const;
};