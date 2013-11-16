#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

using namespace Qt;

ComponentWidget::ComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation) : BaseWidget(graphicalPresentation),component(component){
}

ComponentWidget::~ComponentWidget(){
}

string ComponentWidget::getComponentID(){
    return this->componentID;
}

void ComponentWidget::updateWidget(){
    Rect componentRect = this->component->getRect();
    Point position = componentRect.getPosition();
    this->setText(this->component->getName());
    this->componentID = this->component->getID();
    this->setRect(QRectF(position.getX(),position.getY(),componentRect.getWidth(),componentRect.getHeight()));
    this->doUpdateWidget();
}

Component* ComponentWidget::getComponent(){
    return this->component;
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isWidgetSelected(this->componentID)){
        painter->setPen(QPen(darkGreen,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
        painter->drawPath(this->shape());
    }
}