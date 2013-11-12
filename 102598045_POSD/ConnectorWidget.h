#pragma once

#include "ComponentWidget.h"

class ConnectorWidget : public ComponentWidget{
public:
    ConnectorWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);
    ~ConnectorWidget();

    void updateConnectionPoint();
protected:
    QPainterPath shape() const;
    void doPaint(QPainter* painter);
private:
    QPointF sourcePoint;
    QPointF targetPoint;
};