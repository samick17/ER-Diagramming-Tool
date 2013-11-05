#pragma once

#include "NodeWidget.h"

class AttributeWidget : public NodeWidget{
public:
    AttributeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~AttributeWidget();

    QPainterPath shape() const;
};