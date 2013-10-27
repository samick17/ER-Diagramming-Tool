#pragma once

#include "ComponentWidget.h"

class EntityWidget : public ComponentWidget{
public:
	EntityWidget(Component* component,QGraphicsItem* parent = 0);
	~EntityWidget();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	QRectF boundingRect() const;
};