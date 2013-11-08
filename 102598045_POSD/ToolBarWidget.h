#pragma once

#include <QToolButton>
#include "QActionMap.h"

class ToolBarWidget : public QToolButton{
public:
    ToolBarWidget(QActionMap* actionMap,string actionName,QWidget* parent = 0);
    ~ToolBarWidget();
protected:
    void mousePressEvent(QMouseEvent* mouseEvent);
};