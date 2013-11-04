#pragma once

#include "ComponentWidget.h"

class AttributeWidget : public ComponentWidget{
public:
    AttributeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~AttributeWidget();

    QPainterPath shape() const;
protected:
    void doPaint(QPainter* painter);
};