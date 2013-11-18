#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <string>

class GraphicalPresentation;

using namespace std;

class BaseWidget : public QGraphicsItem{
public:
    BaseWidget(GraphicalPresentation* graphicalPresentation);
    virtual ~BaseWidget();

    virtual void updateWidget() = 0;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    QRectF boundingRect() const;
protected:
    GraphicalPresentation* graphicalPresentation;
    string getText();
    void setText(string text);
    void setRect(QRectF rect);
    bool getIsUnderLine();
    void setUnderLine(bool isUnderLine);
    virtual void doPaint(QPainter* painter) = 0;
    virtual void doUpdateWidget();
private:
    virtual void drawSelectedFrame(QPainter* painter) = 0;
    QRectF rect;
    string text;
    bool isUnderLine;
};