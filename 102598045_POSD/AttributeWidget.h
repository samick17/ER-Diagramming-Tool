#pragma once

#include "NodeWidget.h"

class AttributeWidget : public NodeWidget{
public:
    AttributeWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    ~AttributeWidget();

    QPainterPath shape() const;
protected:
    void doUpdateWidget();
};