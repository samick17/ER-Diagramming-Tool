#pragma once

#include "NodeWidget.h"

class EntityWidget : public NodeWidget{
public:
    EntityWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~EntityWidget();

    QPainterPath shape() const;
};