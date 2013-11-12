#pragma once

#include "NodeWidget.h"

class AttributeWidget : public NodeWidget{
public:
    AttributeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);
    ~AttributeWidget();

    QPainterPath shape() const;
};