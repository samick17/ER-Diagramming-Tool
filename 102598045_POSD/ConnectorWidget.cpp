#include "ConnectorWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <algorithm>
#include "GraphicalPresentation.h"
#include "Connector.h"

using namespace Qt;

ConnectorWidget::ConnectorWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation) : ComponentWidget(componentWidgetData,graphicalPresentation){
    this->updateConnectionPoint();
}

ConnectorWidget::~ConnectorWidget(){
}

QPainterPath ConnectorWidget::shape() const{
    QPainterPath path;
    QPolygonF line;
    line<<sourcePoint<<targetPoint;
    path.addPolygon(line);
    return path;
}

void ConnectorWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->rect,AlignHCenter,QString(this->getText().c_str()));
}

void ConnectorWidget::updateConnectionPoint(){
	HashMap<string,ComponentWidgetData*> componentWidgetDataMap = this->graphicalPresentation->getAllComponentWidgetDatas();

	Connector* connector = static_cast<Connector*>(this->getComponent());

	ComponentWidgetData* sourceWidgetData = componentWidgetDataMap.get(connector->getFirstConnectedNode()->getID());
	ComponentWidgetData* targetWidgetData = componentWidgetDataMap.get(connector->getSecondConnectedNode()->getID());
	
	Point sourceCenterPosition = sourceWidgetData->getRect().getCenterPosition();
	QPointF sourcePoint = QPointF(sourceCenterPosition.getX(),sourceCenterPosition.getY());
	Point targetCenterPosition = targetWidgetData->getRect().getCenterPosition();
	QPointF targetPoint = QPointF(targetCenterPosition.getX(),targetCenterPosition.getY());

	qreal left = sourcePoint.x()<targetPoint.x()?sourcePoint.x():targetPoint.x();
	qreal top = sourcePoint.y()<targetPoint.y()?sourcePoint.y():targetPoint.y();

	this->rect = QRectF(left,top,abs(sourcePoint.x()-targetPoint.x()),abs(sourcePoint.y()-targetPoint.y()));
	this->sourcePoint = sourcePoint;
	this->targetPoint = targetPoint;
}