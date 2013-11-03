#pragma once

#include "ComponentWidget.h"

class AttributeWidget : public ComponentWidget{
public:
    AttributeWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~AttributeWidget();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    void showUnderLine(bool isDisplayUnderLine);
private:
    bool isDisplayUnderLine;
};