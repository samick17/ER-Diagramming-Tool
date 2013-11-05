#pragma once

#include "NodeWidget.h"

class EntityWidget : public NodeWidget{
public:
    EntityWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~EntityWidget();

    QPainterPath shape() const;
};