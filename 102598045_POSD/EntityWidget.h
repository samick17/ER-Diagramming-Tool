#pragma once

#include "ComponentWidget.h"

class EntityWidget : public ComponentWidget{
public:
    EntityWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~EntityWidget();

    QPainterPath shape() const;
protected:
    void doPaint(QPainter* painter);
};