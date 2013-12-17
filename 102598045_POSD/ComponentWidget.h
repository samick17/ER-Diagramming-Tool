#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>
#include "ComponentData.h"

class GraphicalPresentation;

using namespace std;

class ComponentWidget : public QGraphicsItem{
public:
    ComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    virtual ~ComponentWidget();

    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    QRectF boundingRect() const;
    void updateWidget();
    ComponentData* getComponentData();
protected:
    string getText();
    void setText(string text);
    bool getIsUnderLine();
    void setUnderLine(bool isUnderLine);
    virtual void doPaint(QPainter* painter);
    virtual void doUpdateWidget();
    GraphicalPresentation* graphicalPresentation;
    ComponentData* componentData;
private:
    void drawSelectedFrame(QPainter* painter);
    string componentID;
    QRectF rect;
    string text;
    bool isUnderLine;
};