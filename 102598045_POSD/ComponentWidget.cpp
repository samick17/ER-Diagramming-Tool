#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

using namespace Qt;

ComponentWidget::ComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation) : BaseWidget(graphicalPresentation),componentData(componentData){
}

ComponentWidget::~ComponentWidget(){
}

string ComponentWidget::getComponentID(){
    return this->componentID;
}

void ComponentWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->boundingRect(),AlignCenter,QString(this->getText().c_str()));
}

void ComponentWidget::updateWidget(){
    Rect componentRect = this->componentData->getRect();
    Point position = componentRect.getPosition();
    this->setText(this->componentData->getName());
    this->componentID = this->componentData->getID();
    this->setRect(QRectF(position.getX(),position.getY(),componentRect.getWidth(),componentRect.getHeight()));
    this->doUpdateWidget();
}

ComponentData* ComponentWidget::getComponentData(){
    return this->componentData;
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isWidgetSelected(this->componentID)){
        painter->setPen(QPen(darkGreen,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
        painter->drawPath(this->shape());
    }
}