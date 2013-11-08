#include "ToolBarWidget.h"
#include "ActionData.h"
#include "AddDrawableToolBar.h"
#include "GraphicalUI.h"

ToolBarWidget::ToolBarWidget(AddDrawableToolBar* toolBar,QActionMap* actionMap,string actionName) : toolBar(toolBar),QToolButton(toolBar){
    QAction* action = actionMap->getQAction(actionName);
    this->setDefaultAction(action);
    this->setCheckable(true);
}

ToolBarWidget::~ToolBarWidget(){
}