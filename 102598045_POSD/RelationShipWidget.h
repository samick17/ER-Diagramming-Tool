#pragma once

#include "NodeWidget.h"

class RelationShipWidget : public NodeWidget{
public:
    RelationShipWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    ~RelationShipWidget();

    QPainterPath shape() const;
};