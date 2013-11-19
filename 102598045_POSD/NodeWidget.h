#pragma once

#include "ComponentWidget.h"

class NodeWidget : public ComponentWidget{
public:
    NodeWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~NodeWidget();
};