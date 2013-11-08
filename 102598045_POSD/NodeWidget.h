#pragma once

#include "ComponentWidget.h"

class NodeWidget : public ComponentWidget{
public:
    NodeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = NULL);
    ~NodeWidget();

    QPainterPath shape() const = 0;
protected:
    void doPaint(QPainter* painter);
};