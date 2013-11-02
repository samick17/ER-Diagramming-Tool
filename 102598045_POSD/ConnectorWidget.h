#pragma once

#include "ComponentWidget.h"

class ConnectorWidget : public ComponentWidget{
public:
    ConnectorWidget(QGraphicsItem* parent = 0);
    ~ConnectorWidget();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};