#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>

class QGraphicsSceneMouseEvent;
class GraphicalPresentation;

using namespace std;

class ComponentWidget : public QGraphicsItem{
public:
    ComponentWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent = 0);
    ~ComponentWidget();

    void setText(string text);
    void setBoundingRect(QRectF rect);
    void setPos(int positionX,int positionY);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) = 0;
    QRectF boundingRect() const;
protected:
    QRectF rect;
    string text;
    GraphicalPresentation* graphicalPresentation;

    void drawSelectedFrame(QPainter* painter);
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
};