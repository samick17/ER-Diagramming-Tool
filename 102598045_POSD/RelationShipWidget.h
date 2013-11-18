#pragma once

#include "NodeWidget.h"

class RelationShipWidget : public NodeWidget{
public:
    RelationShipWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~RelationShipWidget();

    QPainterPath shape() const;
};