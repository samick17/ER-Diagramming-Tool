#pragma once

#include <QToolBar>
#include "QActionMap.h"
#include "ToolBarWidget.h"
#include "HashMap.h"

class GraphicalUI;

class AddDrawableToolBar : public QToolBar{
public:
    AddDrawableToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~AddDrawableToolBar();

    void selectToolButton(int stateID);
private:
    ToolBarWidget* currentWidget;
    HashMap<int,ToolBarWidget*> toolBarWidgetMap;
};