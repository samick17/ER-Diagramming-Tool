#pragma once

#include "NodeWidget.h"

class RelationShipWidget : public NodeWidget{
public:
    RelationShipWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);
    ~RelationShipWidget();

    QPainterPath shape() const;
};