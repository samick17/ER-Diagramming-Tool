#pragma once

#include <QToolButton>

class AddDrawableToolBar;
class QActionMap;

class ToolBarWidget : public QToolButton{
public:
    ToolBarWidget(AddDrawableToolBar* toolBar,QActionMap* actionMap,unsigned int actionIndex);
    ~ToolBarWidget();
private:
    AddDrawableToolBar* toolBar;
};