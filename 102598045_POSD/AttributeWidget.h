#pragma once

#include "ComponentWidget.h"

class AttributeWidget : public ComponentWidget{
public:
    AttributeWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~AttributeWidget();

    QPainterPath shape() const;
protected:
    void doUpdateWidget();
};