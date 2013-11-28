#pragma once

#include "ComponentWidget.h"

class EntityWidget : public ComponentWidget{
public:
    EntityWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~EntityWidget();

    QPainterPath shape() const;
};