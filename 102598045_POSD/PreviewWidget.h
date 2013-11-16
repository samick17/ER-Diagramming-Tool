#pragma once

#include "BaseWidget.h"

class PreviewWidget : public BaseWidget{
public:
    PreviewWidget(GraphicalPresentation* graphicalPresentation);
    ~PreviewWidget();

    void updateWidget();
    QPainterPath shape() const;
protected:
    void doPaint(QPainter* painter);
    void doUpdateWidget();
private:
    QPointF sourcePoint;
    QPointF targetPoint;
};