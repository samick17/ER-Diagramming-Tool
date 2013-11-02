#pragma once

#include "ComponentWidget.h"

class ConnectorWidget : public ComponentWidget{
public:
    ConnectorWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~ConnectorWidget();

	void setConnectionPoint(QPointF sourcePoint,QPointF targetPoint);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
private:
	QPointF sourcePoint;
	QPointF targetPoint;
};