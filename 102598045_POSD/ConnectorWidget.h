#pragma once

#include "ComponentWidget.h"

class ConnectorWidget : public ComponentWidget{
public:
    ConnectorWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~ConnectorWidget();
protected:
    QPainterPath shape() const;
    void doUpdateWidget();
private:
    QPointF sourcePoint;
    QPointF targetPoint;
};