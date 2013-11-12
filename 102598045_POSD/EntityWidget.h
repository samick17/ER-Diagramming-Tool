#pragma once

#include "NodeWidget.h"

class EntityWidget : public NodeWidget{
public:
    EntityWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);
    ~EntityWidget();

    QPainterPath shape() const;
};