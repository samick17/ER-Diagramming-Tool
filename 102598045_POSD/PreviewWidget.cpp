#include "PreviewWidget.h"

PreviewWidget::PreviewWidget(GraphicalPresentation* graphicalPresentation) : BaseWidget(graphicalPresentation){
}

PreviewWidget::~PreviewWidget(){
}

QPainterPath PreviewWidget::shape() const{
    QPainterPath path;
    return path;
}

void PreviewWidget::doUpdateWidget(){}