#pragma once

#include <QToolButton>
#include "QActionMap.h"

class AddDrawableToolBar;

class ToolBarWidget : public QToolButton{
public:
    ToolBarWidget(AddDrawableToolBar* toolBar,QActionMap* actionMap,unsigned int actionIndex);
    ~ToolBarWidget();
private:
    AddDrawableToolBar* toolBar;
};