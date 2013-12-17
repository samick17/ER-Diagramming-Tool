#pragma once

#include <QToolBar>
#include <QToolButton>

class QActionMap;

class ToolBarWidget : public QToolButton{
public:
    ToolBarWidget(QToolBar* toolBar,QActionMap* actionMap,unsigned int actionIndex);
    ~ToolBarWidget();
};