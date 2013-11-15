#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>
#include "Component.h"

class QGraphicsSceneMouseEvent;
class GraphicalPresentation;

using namespace std;

class ComponentWidget : public QGraphicsItem{
public:
    ComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    ~ComponentWidget();

    Component* getComponent();
    void updateWidget();

    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    QRectF boundingRect() const;
protected:
    Component* component;
    GraphicalPresentation* graphicalPresentation;
    string getText();
    bool getIsUnderLine();
    string getComponentID();
    virtual void doPaint(QPainter* painter) = 0;
    virtual void doUpdateWidget();
private:
    void drawSelectedFrame(QPainter* painter);
    QRectF rect;
    string text;
    bool isUnderLine;
    string componentID;
};