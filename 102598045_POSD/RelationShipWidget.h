#pragma once

#include "ComponentWidget.h"

class RelationShipWidget : public ComponentWidget{
public:
    RelationShipWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~RelationShipWidget();

    QPainterPath shape() const;
};