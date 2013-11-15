#pragma once

#include "ComponentWidget.h"

class ConnectorWidget : public ComponentWidget{
public:
    ConnectorWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    ~ConnectorWidget();
protected:
    QPainterPath shape() const;
    void doPaint(QPainter* painter);
private:
    QPointF sourcePoint;
    QPointF targetPoint;
};