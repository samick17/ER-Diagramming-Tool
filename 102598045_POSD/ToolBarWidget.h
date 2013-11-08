#pragma once

#include <QToolButton>
#include "QActionMap.h"

class AddDrawableToolBar;

class ToolBarWidget : public QToolButton{
public:
    ToolBarWidget(AddDrawableToolBar* toolBar,QActionMap* actionMap,string actionName);
    ~ToolBarWidget();
private:
    AddDrawableToolBar* toolBar;
};