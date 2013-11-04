#pragma once

#include "ComponentWidget.h"

class ConnectorWidget : public ComponentWidget{
public:
    ConnectorWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~ConnectorWidget();

    void setConnectionPoint(QPointF sourcePoint,QPointF targetPoint);
protected:
    void doPaint(QPainter* painter);
private:
    QPointF sourcePoint;
    QPointF targetPoint;
};