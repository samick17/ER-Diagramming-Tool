#pragma once

#include "NodeWidget.h"

class AttributeWidget : public NodeWidget{
public:
    AttributeWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~AttributeWidget();

    QPainterPath shape() const;
protected:
    void doUpdateWidget();
};