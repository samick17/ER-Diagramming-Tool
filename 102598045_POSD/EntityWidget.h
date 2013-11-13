#pragma once

#include "NodeWidget.h"

class EntityWidget : public NodeWidget{
public:
    EntityWidget(Component** component,GraphicalPresentation* graphicalPresentation);
    ~EntityWidget();

    QPainterPath shape() const;
protected:
	void doUpdateWidget();
};