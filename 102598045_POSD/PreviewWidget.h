#pragma once

#include "BaseWidget.h"

class PreviewWidget : public BaseWidget{
public:
    PreviewWidget(GraphicalPresentation* graphicalPresentation);
    ~PreviewWidget();

    QPainterPath shape() const;
protected:
    void doUpdateWidget();
};